#include "Staff.h"
#include <iostream>

Staff::Staff() : Employee() { role = "Staff"; }

Staff::Staff(int empId, std::string empName) : Employee(empId, empName, "Staff") {
    restrictedActions.push_back("Access Admin Files");
    restrictedActions.push_back("Delete System Logs");
    restrictedActions.push_back("Modify User Roles");
}

Staff::~Staff() {
    std::cout << "  (Staff destroyed: " << name << ")\n";
}

bool Staff::checkThreat(const std::string& action) {
    bool flagged = false;
    for (size_t i = 0; i < restrictedActions.size(); i++) {
        if (action == restrictedActions[i]) {
            flagged = true;
            break;
        }
    }

    Activity act("Staff Action", action, flagged);
    logActivity(act);

    if (flagged)
        std::cout << "[Staff Check] \"" << action << "\" -> FLAGGED AS THREAT (Unauthorized Access)\n";
    else
        std::cout << "[Staff Check] \"" << action << "\" -> Allowed (Normal Activity)\n";

    return flagged;
}

void Staff::display() const {
    std::cout << "[STAFF] ";
    Employee::display();
    std::cout << " | Access Level: RESTRICTED\n";
}
