#ifndef SENIORADMIN_H
#define SENIORADMIN_H

#include "Admin.h"
#include "AuditTrail.h"

// ============================================================
// SeniorAdmin
//  - Multilevel Inheritance: Employee -> Admin -> SeniorAdmin (Lesson 7B)
//  - Multiple Inheritance: also implements the AuditTrail
//    interface alongside Admin (Lesson 7B)
// ============================================================
class SeniorAdmin : public Admin, public AuditTrail {
public:
    SeniorAdmin();
    SeniorAdmin(int empId, std::string empName);
    ~SeniorAdmin() override;

    bool checkThreat(const std::string& action) override;
    void display() const override;

    // From AuditTrail (Multiple Inheritance)
    void exportAudit() const override;
};

#endif
