#include "ThreatCounter.h"

ThreatCounter::ThreatCounter() : count(0) {}

int ThreatCounter::getCount() const { return count; }

// Prefix: increment first, then return updated object
ThreatCounter& ThreatCounter::operator++() {
    ++count;
    return *this;
}

// Postfix: keep old value, increment, return the old value
ThreatCounter ThreatCounter::operator++(int) {
    ThreatCounter temp = *this;
    count++;
    return temp;
}

std::ostream& operator<<(std::ostream& out, const ThreatCounter& tc) {
    out << "Total Threats Detected: " << tc.count;
    return out;
}
