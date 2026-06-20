FROM node:18-bullseye

# Install g++ compiler
RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy application files
COPY . .

# Compile the C++ core engine
RUN g++ -O3 -std=c++14 ITDS/src/*.cpp -o InsiderThreatDetectionSystem -I ITDS/include

# Install npm dependencies
RUN npm install

# Expose port (default is 7860 for Hugging Face Spaces)
EXPOSE 7860
ENV PORT=7860

# Start Node.js backend
CMD ["node", "server.js"]
