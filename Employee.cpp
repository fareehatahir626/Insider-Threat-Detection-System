#include "Employee.h"
#include <iostream>

Employee::Employee() : id(0), name("Unknown"), role("Unknown") {}

Employee::Employee(int empId, std::string empName, std::string empRole)
    : id(empId), name(empName), role(empRole) {}

Employee::~Employee() {
    std::cout << "  (Employee base destroyed for: " << name << ")\n";
}

int Employee::getId() const { return id; }
std::string Employee::getName() const { return name; }
std::string Employee::getRole() const { return role; }

// Overload 1: log a ready-made Activity object
void Employee::logActivity(const Activity& act) {
    activityLog.push_back(act);
}

// Overload 2: log a plain description (overloaded by parameter type)
void Employee::logActivity(const std::string& desc) {
    Activity act("General", desc, false);
    activityLog.push_back(act);
}

void Employee::viewLogs() const {
    std::cout << "\n--- Activity Log for " << name << " (ID: " << id << ") ---\n";
    if (activityLog.empty()) {
        std::cout << "No activities recorded.\n";
        return;
    }
    for (size_t i = 0; i < activityLog.size(); i++) {
        std::cout << i + 1 << ". " << activityLog[i] << std::endl;
    }
}

bool Employee::hasThreatHistory() const {
    for (size_t i = 0; i < activityLog.size(); i++) {
        if (activityLog[i].isFlagged())
            return true;
    }
    return false;
}

void Employee::display() const {
    std::cout << "ID: " << id << " | Name: " << name << " | Role: " << role;
}

bool Employee::operator==(const Employee& other) const {
    return this->id == other.id;     // `this` pointer used explicitly (Lesson 8)
}

bool Employee::operator!=(const Employee& other) const {
    return !(*this == other);
}

bool Employee::operator<(const Employee& other) const {
    return this->id < other.id;
}

bool Employee::operator>(const Employee& other) const {
    return this->id > other.id;
}
