#include "Admin.h"
#include <iostream>

Admin::Admin() : Employee() { role = "Admin"; }

// Parameterized constructor passes args up to the base constructor
Admin::Admin(int empId, std::string empName) : Employee(empId, empName, "Admin") {}

Admin::~Admin() {
    std::cout << "  (Admin destroyed: " << name << ")\n";
}

bool Admin::checkThreat(const std::string& action) {
    Activity act("Admin Action", action, false);
    logActivity(act);
    std::cout << "[Admin Check] \"" << action << "\" -> Allowed (Full Access, No Restrictions)\n";
    return false;
}

void Admin::display() const {
    std::cout << "[ADMIN] ";
    Employee::display();
    std::cout << " | Access Level: FULL\n";
}
