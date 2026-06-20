#ifndef UTILS_H
#define UTILS_H

#include <vector>

// ============================================================
// Function Templates (Lesson 9)
// ============================================================

// Generic Function: search any vector of pointers by ID
template <typename T>
T findById(const std::vector<T>& items, int searchId) {
    for (std::size_t i = 0; i < items.size(); i++) {
        if (items[i]->getId() == searchId)
            return items[i];
    }
    return nullptr;
}

// Generic Function: call display() on every item in a vector
template <typename T>
void printAll(const std::vector<T>& items) {
    for (std::size_t i = 0; i < items.size(); i++) {
        items[i]->display();
    }
}

// Function Template with Multiple (different) Type Arguments
template <typename T1, typename T2>
bool isSameRole(const T1* a, const T2* b) {
    return a->getRole() == b->getRole();
}

#endif
