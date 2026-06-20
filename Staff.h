#ifndef STAFF_H
#define STAFF_H

#include "Employee.h"
#include <vector>

// ============================================================
// Staff - Derived Class (Restricted Access)
// ============================================================
class Staff : public Employee {
private:
    std::vector<std::string> restrictedActions;

public:
    Staff();
    Staff(int empId, std::string empName);
    ~Staff() override;

    // Override: Staff actions are checked against the restricted list
    bool checkThreat(const std::string& action) override;

    void display() const override;
};

#endif
