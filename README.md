# Insider Threat Detection System

**OOP Project (CS112)**
Members: Maira Tahir | Fareeha Tahir | Khurram Ali Saif
Roll No: 2540031 | 2540041 | 2540026

## Overview

A menu-driven C++ console application that simulates a cybersecurity
environment where employee activities are logged and checked for
insider-threat behaviour, based on role (`Admin`, `Staff`, `SeniorAdmin`).

This project uses **only** concepts covered in Lessons 6, 7A, 7B, 8, and
9 of the course.

## Project Structure

```
ITDS/
├── include/              Header files (class declarations)
│   ├── FileSize.h
│   ├── ThreatCounter.h
│   ├── Activity.h
│   ├── Employee.h
│   ├── AuditTrail.h
│   ├── Admin.h
│   ├── Staff.h
│   ├── SeniorAdmin.h
│   ├── Repository.h      (class template)
│   ├── Utils.h            (function templates)
│   └── SecurityManager.h
├── src/                   Implementation files (.cpp)
│   ├── FileSize.cpp
│   ├── ThreatCounter.cpp
│   ├── Activity.cpp
│   ├── Employee.cpp
│   ├── Admin.cpp
│   ├── Staff.cpp
│   ├── SeniorAdmin.cpp
│   ├── SecurityManager.cpp
│   └── main.cpp
├── Makefile
└── README.md
```

## How to Build & Run

**Using make (recommended):**
```
make
./InsiderThreatDetectionSystem
```

**Without make:**
```
g++ -std=c++14 -Wall -Iinclude src/*.cpp -o InsiderThreatDetectionSystem
./InsiderThreatDetectionSystem
```

**Clean build files:**
```
make clean
```

## Sample Output

Adding a Staff member, having them attempt a restricted action, viewing
their log, and checking the threat summary:

```
Welcome to the Insider Threat Detection System

========== INSIDER THREAT DETECTION SYSTEM ==========
1.  Add Admin
2.  Add Staff
3.  Add Senior Admin
4.  Perform Activity (Check Threat)
5.  View Employee Logs
6.  View All Employees
7.  Identify Employee Type (RTTI Demo)
8.  Sort Employees by ID (STL Algorithm Demo)
9.  Show Threat Summary (Threat Counter Demo)
10. Export Senior Admin Audit
11. Compare Two Employees' Roles (Multi-Type Template Demo)
12. Exit
=======================================================
Enter your choice: 2
Enter Staff ID: 102
Enter Staff Name: Sara
Staff added successfully.

Enter your choice: 4
Enter Employee ID: 102
Enter action performed (e.g. Login, Access Admin Files): Access Admin Files
[Staff Check] "Access Admin Files" -> FLAGGED AS THREAT (Unauthorized Access)

Enter your choice: 5
Enter Employee ID: 102

--- Activity Log for Sara (ID: 102) ---
1. [Staff Action] Access Admin Files  -->  THREAT DETECTED

Enter your choice: 9

Total Threats Detected: 1
Employees with at least one flagged activity: 1

Enter your choice: 12
Exiting system...
  (Staff destroyed: Sara)
  (Employee base destroyed for: Sara)
```

## Concept-to-File Map (for viva / explanation)

| Syllabus Topic                              | Lesson | Where it lives |
|----------------------------------------------|--------|-----------------|
| Classes & Objects                             | -      | All classes in `include/` |
| Encapsulation (private members + getters)     | -      | `Employee.h/.cpp` |
| Default + Parameterized Constructors          | -      | All classes |
| Base/Derived Classes, Protected Members       | 7A     | `Employee.h` (protected), `Admin`, `Staff` |
| Passing Arguments to Base Constructors        | 7A     | `Admin(int,string)`, `Staff(int,string)`, `SeniorAdmin(int,string)` |
| Constructors/Destructors in Inheritance       | 7A     | Destructor chain printed in `~Employee`, `~Admin`, `~Staff`, `~SeniorAdmin` |
| Function Overriding                           | 7A/8   | `checkThreat()`, `display()` |
| Abstract Base Class / Pure Virtual Function   | 7B/8   | `Employee::checkThreat() = 0` |
| Aggregation (Has-A Relationship)              | 7B     | `Employee` has-a `vector<Activity>`; `SecurityManager` has-a `Repository<Employee*>` and `ThreatCounter` |
| Multilevel Inheritance                        | 7B     | `Employee -> Admin -> SeniorAdmin` |
| Multiple Inheritance                          | 7B     | `SeniorAdmin : public Admin, public AuditTrail` |
| Hierarchical Inheritance                      | 7B     | `Employee -> Admin`, `Employee -> Staff` |
| Virtual Functions / Runtime Polymorphism      | 8      | `checkThreat()`, `display()` called through `Employee*` |
| `this` Pointer                                | 8      | `Employee::operator==`, `operator<`, etc. |
| RTTI: `typeid`, `dynamic_cast`, Upcasting/Downcasting | 8 | `SecurityManager::identifyType()` |
| Function Templates                            | 9      | `Utils.h` (`findById`, `printAll`, `isSameRole`) |
| Class Templates                               | 9      | `Repository.h` |
| STL Vector + member functions (push_back, pop_back, front, back, at, insert, swap, empty, clear, size) | 9 | `Repository.h` |
| STL Iterators                                  | 9      | `SecurityManager::~SecurityManager()` cleanup loop |
| STL Algorithms (`sort`, `count_if`)            | 9      | `SecurityManager::sortEmployeesById()`, `countThreatenedEmployees()` |
| Unary Operator Overloading (prefix/postfix `++`) | 6   | `ThreatCounter.h/.cpp` |
| Binary Operator Overloading (Object+Object, Object+Value) | 6 | `FileSize.h/.cpp` |
| Arithmetic Assignment Operator (`+=`)          | 6      | `FileSize::operator+=` |
| Comparison Operators (`==`, `!=`, `>`, `<`)    | 6      | `FileSize` and `Employee` |
| Stream Operators (`<<`, `>>`)                  | 6      | `FileSize`, `Activity`, `ThreatCounter` |
| Function Overloading (Compile-Time Polymorphism) | 8    | `Employee::logActivity()` (two versions) |

## Notes

Hybrid Inheritance / the Diamond Problem was studied in Lesson 7B but is
deliberately **not** forced into this project — `SeniorAdmin`'s multiple
inheritance (`Admin` + `AuditTrail`) does not create a diamond, since
`AuditTrail` does not derive from `Employee`. This keeps the design clean
while still demonstrating multiple inheritance correctly.
