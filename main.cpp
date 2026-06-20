/*
 ====================================================================
  OOP PROJECT - Insider Threat Detection System
  Members : Maira Tahir | Fareeha Tahir | Khurram Ali Saif
  Roll No : 2540031 | 2540041 | 2540026
 ====================================================================
  See README.md for the full concept-to-file map used for this
  project (which file demonstrates which syllabus topic).
 ====================================================================
*/

#include <iostream>
#include <string>
#include "Admin.h"
#include "Staff.h"
#include "SeniorAdmin.h"
#include "SecurityManager.h"
#include "Utils.h"

using namespace std;

void showMenu() {
    cout << "\n========== INSIDER THREAT DETECTION SYSTEM ==========\n";
    cout << "1.  Add Admin\n";
    cout << "2.  Add Staff\n";
    cout << "3.  Add Senior Admin\n";
    cout << "4.  Perform Activity (Check Threat)\n";
    cout << "5.  View Employee Logs\n";
    cout << "6.  View All Employees\n";
    cout << "7.  Identify Employee Type (RTTI Demo)\n";
    cout << "8.  Sort Employees by ID (STL Algorithm Demo)\n";
    cout << "9.  Show Threat Summary (Threat Counter Demo)\n";
    cout << "10. Export Senior Admin Audit\n";
    cout << "11. Compare Two Employees' Roles (Multi-Type Template Demo)\n";
    cout << "12. Exit\n";
    cout << "=======================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    SecurityManager manager;
    int choice;

    cout << "Welcome to the Insider Threat Detection System\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int id; string name;
            cout << "Enter Admin ID: "; cin >> id;
            cout << "Enter Admin Name: "; cin.ignore(); getline(cin, name);
            manager.addEmployee(new Admin(id, name));
            cout << "Admin added successfully.\n";
            break;
        }
        case 2: {
            int id; string name;
            cout << "Enter Staff ID: "; cin >> id;
            cout << "Enter Staff Name: "; cin.ignore(); getline(cin, name);
            manager.addEmployee(new Staff(id, name));
            cout << "Staff added successfully.\n";
            break;
        }
        case 3: {
            int id; string name;
            cout << "Enter Senior Admin ID: "; cin >> id;
            cout << "Enter Senior Admin Name: "; cin.ignore(); getline(cin, name);
            manager.addEmployee(new SeniorAdmin(id, name));
            cout << "Senior Admin added successfully.\n";
            break;
        }
        case 4: {
            int id; string action;
            cout << "Enter Employee ID: "; cin >> id;
            cout << "Enter action performed (e.g. Login, Access Admin Files): ";
            cin.ignore(); getline(cin, action);
            manager.performActivity(id, action);   // Runtime Polymorphism
            break;
        }
        case 5: {
            int id;
            cout << "Enter Employee ID: "; cin >> id;
            Employee* emp = manager.findEmployee(id);
            if (emp == nullptr) cout << "Employee not found.\n";
            else emp->viewLogs();
            break;
        }
        case 6:
            manager.showAllEmployees();
            break;
        case 7: {
            int id;
            cout << "Enter Employee ID: "; cin >> id;
            manager.identifyType(id);
            break;
        }
        case 8:
            manager.sortEmployeesById();
            break;
        case 9:
            manager.showThreatSummary();
            break;
        case 10: {
            int id;
            cout << "Enter Senior Admin ID: "; cin >> id;
            Employee* emp = manager.findEmployee(id);
            SeniorAdmin* sa = dynamic_cast<SeniorAdmin*>(emp);
            if (sa == nullptr) cout << "No Senior Admin found with that ID.\n";
            else sa->exportAudit();
            break;
        }
        case 11: {
            int id1, id2;
            cout << "Enter first Employee ID: "; cin >> id1;
            cout << "Enter second Employee ID: "; cin >> id2;
            Employee* e1 = manager.findEmployee(id1);
            Employee* e2 = manager.findEmployee(id2);
            if (e1 == nullptr || e2 == nullptr) {
                cout << "One or both employees not found.\n";
                break;
            }
            // Function Template with multiple type arguments (Lesson 9)
            bool same = isSameRole(e1, e2);
            cout << (same ? "Both employees share the same role.\n"
                          : "Employees have different roles.\n");
            break;
        }
        case 12:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 12);

    return 0;   // SecurityManager destructor cleans up all Employee* pointers
}
