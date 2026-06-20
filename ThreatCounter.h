#ifndef THREATCOUNTER_H
#define THREATCOUNTER_H

#include <iostream>

// ============================================================
// ThreatCounter - a simple counter for system-wide flagged threats
// Demonstrates Lesson 6: Unary Operator Overloading
// (Prefix ++ and Postfix ++), same style as the
// "Unary Operator Practice Question (Battery System)"
// ============================================================
class ThreatCounter {
private:
    int count;

public:
    ThreatCounter();

    int getCount() const;

    // Prefix Increment: ++counter
    ThreatCounter& operator++();
    // Postfix Increment: counter++
    ThreatCounter operator++(int);

    friend std::ostream& operator<<(std::ostream& out, const ThreatCounter& tc);
};

#endif
