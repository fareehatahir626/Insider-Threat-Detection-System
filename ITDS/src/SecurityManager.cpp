#include "SecurityManager.h"
#include "Admin.h"
#include "Staff.h"
#include "SeniorAdmin.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

#include <fstream>
#include <sstream>
#include <string>

SecurityManager::SecurityManager() {
    loadData("employees.txt");
}

SecurityManager::~SecurityManager() {
    saveData("employees.txt");
    // Cleanup using an explicit STL iterator (Lesson 9: Iterators)
    std::vector<Employee*>& all = employees.getAll();
    for (std::vector<Employee*>::iterator it = all.begin(); it != all.end(); ++it) {
        delete (*it);
    }
}

void SecurityManager::saveData(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    const std::vector<Employee*>& all = employees.getAll();
    for (size_t i = 0; i < all.size(); ++i) {
        outFile << all[i]->getRole() << "," << all[i]->getId() << "," << all[i]->getName() << "\n";
    }
    outFile.close();
}

void SecurityManager::loadData(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string roleStr, idStr, name;
        if (std::getline(ss, roleStr, ',') && std::getline(ss, idStr, ',') && std::getline(ss, name)) {
            try {
                int id = std::stoi(idStr);
                if (findEmployee(id) != nullptr) continue; // Skip duplicates
                if (roleStr == "Admin") addEmployee(new Admin(id, name));
                else if (roleStr == "Staff") addEmployee(new Staff(id, name));
                else if (roleStr == "SeniorAdmin") addEmployee(new SeniorAdmin(id, name));
            } catch (...) {
                // Ignore parse errors
            }
        }
    }
    inFile.close();
}

void SecurityManager::addEmployee(Employee* emp) {
    employees.add(emp);   // Repository<T>::add() -> wraps vector push_back
}

Employee* SecurityManager::findEmployee(int id) {
    return findById(employees.getAll(), id);   // Function Template (Lesson 9)
}

void SecurityManager::performActivity(int id, const std::string& action) {
    Employee* emp = findEmployee(id);
    if (emp == nullptr) {
        std::cout << "Employee not found.\n";
        return;
    }
    bool flagged = emp->checkThreat(action);   // Runtime Polymorphism
    if (flagged) {
        ++threatCounter;   // Prefix increment (Lesson 6)
    }
}

void SecurityManager::showAllEmployees() const {
    std::cout << "\n--- All Employees ---\n";
    printAll(employees.getAll());   // Function Template (Lesson 9)
}

void SecurityManager::identifyType(int id) const {
    Employee* emp = findById(employees.getAll(), id);
    if (emp == nullptr) {
        std::cout << "Employee not found.\n";
        return;
    }

    // RTTI: typeid Operator (Lesson 8)
    std::cout << "Compiler-reported type (typeid): " << typeid(*emp).name() << "\n";

    // RTTI: dynamic_cast for safe Downcasting (most-derived type checked first)
    if (dynamic_cast<SeniorAdmin*>(emp)) {
        std::cout << emp->getName() << " is identified as a SENIOR ADMIN (dynamic_cast successful).\n";
    } else if (dynamic_cast<Admin*>(emp)) {
        std::cout << emp->getName() << " is identified as an ADMIN (dynamic_cast successful).\n";
    } else if (dynamic_cast<Staff*>(emp)) {
        std::cout << emp->getName() << " is identified as STAFF (dynamic_cast successful).\n";
    }

    // Upcasting (always safe, implicit): derived -> base
    Employee* base = emp;
    std::cout << "Upcast to Employee* successful, base role reads: " << base->getRole() << "\n";
}

void SecurityManager::sortEmployeesById() {
    std::vector<Employee*>& all = employees.getAll();
    // STL Algorithm: sort, using overloaded operator< (Lesson 6 + Lesson 9)
    std::sort(all.begin(), all.end(), [](Employee* a, Employee* b) {
        return *a < *b;
    });
    std::cout << "Employees sorted by ID.\n";
}

int SecurityManager::countThreatenedEmployees() const {
    const std::vector<Employee*>& all = employees.getAll();
    // STL Algorithm: count_if (Lesson 9)
    return static_cast<int>(std::count_if(all.begin(), all.end(), [](Employee* e) {
        return e->hasThreatHistory();
    }));
}

void SecurityManager::showThreatSummary() const {
    std::cout << "\n" << threatCounter << "\n";
    std::cout << "Employees with at least one flagged activity: "
              << countThreatenedEmployees() << "\n";
}
