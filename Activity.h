#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <iostream>
#include "FileSize.h"

// ============================================================
// Activity - represents a single action performed by an employee
// (login, file access, data operation). Holds an optional
// FileSize to track how much data was touched.
// ============================================================
class Activity {
private:
    std::string actionType;
    std::string description;
    bool threatFlag;
    FileSize dataAccessed;

public:
    // Default Constructor
    Activity();
    // Parameterized Constructor
    Activity(std::string type, std::string desc, bool flag = false, FileSize size = FileSize());

    // Encapsulation: controlled access via public getters
    std::string getActionType() const;
    std::string getDescription() const;
    bool isFlagged() const;
    FileSize getDataAccessed() const;

    // Stream Operator Overloading (Lesson 6)
    friend std::ostream& operator<<(std::ostream& out, const Activity& act);
};

#endif
