#ifndef SECURITYMANAGER_H
#define SECURITYMANAGER_H

#include "Employee.h"
#include "Repository.h"
#include "ThreatCounter.h"
#include <string>

// ============================================================
// SecurityManager
//  - Aggregation: "has-a" Repository<Employee*> and "has-a"
//    ThreatCounter (Lesson 7B: Aggregation / Has-A Relationship)
//  - Uses STL Algorithms (sort, count_if) and Iterators (Lesson 9)
//  - Uses RTTI (typeid, dynamic_cast) to identify employee types
// ============================================================
class SecurityManager {
private:
    Repository<Employee*> employees;
    ThreatCounter threatCounter;

public:
    SecurityManager();
    ~SecurityManager();

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

    void addEmployee(Employee* emp);
    Employee* findEmployee(int id);

    void performActivity(int id, const std::string& action);
    void showAllEmployees() const;
    void identifyType(int id) const;       // RTTI demo
    void sortEmployeesById();              // STL Algorithm: sort + operator<
    int countThreatenedEmployees() const;  // STL Algorithm: count_if
    void showThreatSummary() const;
};

#endif
