#ifndef ADMIN_H
#define ADMIN_H

#include "Employee.h"

// ============================================================
// Admin - Derived Class (Full Access)
// Demonstrates Inheritance: constructor passes arguments to
// the Employee base constructor (Lesson 7A).
// ============================================================
class Admin : public Employee {
public:
    Admin();
    Admin(int empId, std::string empName);
    ~Admin() override;

    // Override: Admin has full access, nothing is ever flagged
    bool checkThreat(const std::string& action) override;

    void display() const override;
};

#endif
