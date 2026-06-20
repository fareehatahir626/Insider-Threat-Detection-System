#ifndef AUDITTRAIL_H
#define AUDITTRAIL_H

// ============================================================
// AuditTrail - a pure abstract interface.
// SeniorAdmin inherits from BOTH Admin and AuditTrail, which
// demonstrates Multiple Inheritance (Lesson 7B).
// ============================================================
class AuditTrail {
public:
    virtual void exportAudit() const = 0;
    virtual ~AuditTrail() {}
};

#endif
