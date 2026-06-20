const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static(__dirname));

// ─── C++ Process Manager ───────────────────────────────────────────────────
// We keep ONE persistent C++ process per "session" (in-memory map by sessionId).
// The UI sends commands; the server pipes stdin and reads stdout until the next menu prompt.

const BINARY = path.join(__dirname, process.platform === 'win32' ? './InsiderThreatDetectionSystem.exe' : './InsiderThreatDetectionSystem');
const PROMPT_RE = /Enter your choice:\s*$/;

const sessions = {}; // sessionId -> { proc, buffer, waiters, lastActive }

// Kill sessions inactive for >15 minutes to prevent Zombie Process leaks
setInterval(() => {
  const now = Date.now();
  for (const [id, session] of Object.entries(sessions)) {
    if (now - session.lastActive > 15 * 60 * 1000) {
      session.proc.kill();
      delete sessions[id];
      console.log(`Killed idle session: ${id}`);
    }
  }
}, 60000);

function createSession(sessionId) {
  const proc = spawn(BINARY, [], { stdio: ['pipe', 'pipe', 'pipe'] });
  const session = { proc, buffer: '', waiters: [], lastActive: Date.now() };
  sessions[sessionId] = session;

  proc.stdout.on('data', (chunk) => {
    session.buffer += chunk.toString();
    flush(session);
  });
  proc.stderr.on('data', (chunk) => {
    session.buffer += chunk.toString();
    flush(session);
  });
  proc.on('close', () => {
    // resolve any remaining waiters
    const cb = session.waiters.shift();
    if (cb) cb(session.buffer);
    session.buffer = '';
    delete sessions[sessionId];
  });
  return session;
}

function flush(session) {
  if (session.waiters.length === 0) return;
  // Release waiter when we see the menu prompt again (or process exited)
  if (PROMPT_RE.test(session.buffer)) {
    const cb = session.waiters.shift();
    const out = session.buffer;
    session.buffer = '';
    cb(out);
  }
}

// Send lines to the C++ process and collect output until next menu prompt
function runCommand(sessionId, lines) {
  return new Promise((resolve, reject) => {
    let session = sessions[sessionId];
    if (!session || session.proc.exitCode !== null) {
      session = createSession(sessionId);
      // Wait for the initial welcome + menu prompt
      session.waiters.push(() => {
        sendLines(session, lines, resolve, reject);
      });
    } else {
      session.lastActive = Date.now();
      sendLines(session, lines, resolve, reject);
    }
  });
}

function sendLines(session, lines, resolve, reject) {
  const timeout = setTimeout(() => {
    const cb = session.waiters.indexOf(resolve);
    if (cb > -1) session.waiters.splice(cb, 1);
    resolve(session.buffer || '[timeout]');
    session.buffer = '';
  }, 5000);

  session.waiters.push((out) => {
    clearTimeout(timeout);
    resolve(out);
  });

  for (const line of lines) {
    session.proc.stdin.write(line + '\n');
  }
}

// ─── Routes ───────────────────────────────────────────────────────────────

// Start / ping session → get initial menu output
app.post('/api/start', (req, res) => {
  const { sessionId } = req.body;
  const session = createSession(sessionId);
  session.waiters.push((out) => res.json({ output: out }));
});

// Generic command endpoint: { sessionId, lines: ["4","101","Login"] }
app.post('/api/command', async (req, res) => {
  const { sessionId, lines } = req.body;
  if (!sessionId || !lines) return res.status(400).json({ error: 'Missing sessionId or lines' });
  try {
    const output = await runCommand(sessionId, lines);
    res.json({ output: clean(output) });
  } catch (e) {
    res.status(500).json({ error: e.message });
  }
});

// Exit session cleanly
app.post('/api/exit', (req, res) => {
  const { sessionId } = req.body;
  const session = sessions[sessionId];
  if (session) {
    session.proc.stdin.write('12\n');
    setTimeout(() => {
      if (sessions[sessionId]) session.proc.kill();
    }, 1000);
  }
  res.json({ ok: true });
});

function clean(str) {
  // Strip the repeated menu banners from output, keep only the result lines
  return str
    .replace(/\n={10,}\n[\s\S]*?={10,}\nEnter your choice:\s*/g, '')
    .trim();
}

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`ITDS server running on http://localhost:${PORT}`));
