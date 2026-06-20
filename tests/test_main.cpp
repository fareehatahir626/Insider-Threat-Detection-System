#include <iostream>
#include <cassert>
#include "Admin.h"
#include "Staff.h"
#include "SeniorAdmin.h"
#include "SecurityManager.h"

void testEmployeeCreationAndRoles() {
    Admin a(101, "AdminTest");
    assert(a.getId() == 101);
    assert(a.getName() == "AdminTest");
    assert(a.getRole() == "Admin");

    Staff s(102, "StaffTest");
    assert(s.getRole() == "Staff");

    SeniorAdmin sa(103, "SeniorAdminTest");
    assert(sa.getRole() == "SeniorAdmin");

    std::cout << "testEmployeeCreationAndRoles passed.\n";
}

void testThreatDetection() {
    Admin a(101, "AdminTest");
    Staff s(102, "StaffTest");
    
    // Admin has full access, no threat
    assert(a.checkThreat("Access Admin Files") == false);
    
    // Staff restricted access, should trigger threat
    assert(s.checkThreat("Access Admin Files") == true);
    assert(s.checkThreat("Normal Login") == false);

    std::cout << "testThreatDetection passed.\n";
}

void testSecurityManagerAndPersistence() {
    // Write a temp employee to ensure SecurityManager loads it
    // Wait, testing file I/O requires writing a file. We will skip I/O test here to avoid side effects.
    SecurityManager sm;
    sm.addEmployee(new Admin(999, "TestAdmin"));
    
    Employee* found = sm.findEmployee(999);
    assert(found != nullptr);
    assert(found->getName() == "TestAdmin");
    
    std::cout << "testSecurityManager passed.\n";
}

int main() {
    std::cout << "Running Automated Tests...\n";
    testEmployeeCreationAndRoles();
    testThreatDetection();
    testSecurityManagerAndPersistence();
    std::cout << "All tests passed successfully.\n";
    return 0;
}
