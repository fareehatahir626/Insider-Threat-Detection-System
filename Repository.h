#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <algorithm>
#include <cstddef>

// ============================================================
// Repository<T> - Class Template (Lesson 9: Class Templates)
// A generic, reusable container wrapping an STL vector.
// Demonstrates: Template Class Syntax, Generic Classes,
// Code Reusability, and the STL Vector member functions
// (push_back, pop_back, front, back, at, insert, swap,
//  empty, clear, size).
// ============================================================
template <typename T>
class Repository {
private:
    std::vector<T> items;

public:
    void add(const T& item) { items.push_back(item); }
    void removeLast() { if (!items.empty()) items.pop_back(); }
    void insertAt(std::size_t index, const T& item) { items.insert(items.begin() + index, item); }
    void swapItems(std::size_t i, std::size_t j) { std::swap(items[i], items[j]); }
    void clearAll() { items.clear(); }

    bool empty() const { return items.empty(); }
    std::size_t size() const { return items.size(); }
    T front() const { return items.front(); }
    T back() const { return items.back(); }
    T at(std::size_t index) const { return items.at(index); }

    std::vector<T>& getAll() { return items; }
    const std::vector<T>& getAll() const { return items; }
};

#endif
