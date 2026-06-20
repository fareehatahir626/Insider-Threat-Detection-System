#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "Activity.h"

// ============================================================
// Employee - Abstract Base Class
// Contains a pure virtual function (checkThreat), so Employee
// itself can never be instantiated directly (Lesson 8: Abstract
// Classes and Pure Virtual Functions).
// ============================================================
class Employee {
protected:
    int id;                          // Encapsulation: hidden from outside
    std::string name;
    std::string role;
    std::vector<Activity> activityLog; // Aggregation: Employee "has-a" Activities

public:
    // Default Constructor
    Employee();
    // Parameterized Constructor
    Employee(int empId, std::string empName, std::string empRole);

    // Virtual destructor -> correct cleanup through base pointers
    virtual ~Employee();

    // Encapsulation: Getters
    int getId() const;
    std::string getName() const;
    std::string getRole() const;

    // Function Overloading (Compile-Time Polymorphism, Lesson 8)
    void logActivity(const Activity& act);
    void logActivity(const std::string& desc);

    void viewLogs() const;
    bool hasThreatHistory() const;   // true if any logged activity was flagged

    // Pure Virtual Function -> makes Employee Abstract
    virtual bool checkThreat(const std::string& action) = 0;

    // Virtual Function -> overridden by derived classes (Runtime Polymorphism)
    virtual void display() const;

    // Operator Overloading (Lesson 6) - uses the `this` pointer explicitly
    bool operator==(const Employee& other) const;
    bool operator!=(const Employee& other) const;
    bool operator<(const Employee& other) const;
    bool operator>(const Employee& other) const;
};

#endif
