#include "SeniorAdmin.h"
#include <iostream>

SeniorAdmin::SeniorAdmin() : Admin() { role = "SeniorAdmin"; }

// Constructor passes arguments up through TWO levels: SeniorAdmin -> Admin -> Employee
SeniorAdmin::SeniorAdmin(int empId, std::string empName) : Admin(empId, empName) {
    role = "SeniorAdmin";
}

SeniorAdmin::~SeniorAdmin() {
    std::cout << "  (SeniorAdmin destroyed: " << name << ")\n";
}

bool SeniorAdmin::checkThreat(const std::string& action) {
    // Re-uses Admin's base behaviour (full access), then adds an audit note
    bool result = Admin::checkThreat(action);
    logActivity("Audited by SeniorAdmin: " + action);
    return result;
}

void SeniorAdmin::display() const {
    std::cout << "[SENIOR ADMIN] ";
    Employee::display();
    std::cout << " | Access Level: FULL + AUDIT\n";
}

void SeniorAdmin::exportAudit() const {
    std::cout << "\n--- Audit Export for " << name << " ---\n";
    viewLogs();
}
