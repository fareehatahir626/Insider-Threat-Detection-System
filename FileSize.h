#ifndef FILESIZE_H
#define FILESIZE_H

#include <iostream>

// ============================================================
// FileSize - represents an amount of data (in KB)
// Demonstrates Lesson 6: Binary Operator Overloading,
// Comparison Operators, Compound Assignment, Stream Operators
// ============================================================
class FileSize {
private:
    double sizeInKB;

public:
    FileSize();
    FileSize(double kb);

    double getSize() const;

    // Binary Operator Overloading: Object + Object
    FileSize operator+(const FileSize& other) const;
    // Binary Operator Overloading: Object + Value
    FileSize operator+(double extraKB) const;

    // Arithmetic Assignment Operator
    FileSize& operator+=(const FileSize& other);

    // Comparison Operators
    bool operator==(const FileSize& other) const;
    bool operator!=(const FileSize& other) const;
    bool operator>(const FileSize& other) const;
    bool operator<(const FileSize& other) const;

    // Stream Operators (<< and >>)
    friend std::ostream& operator<<(std::ostream& out, const FileSize& fs);
    friend std::istream& operator>>(std::istream& in, FileSize& fs);
};

#endif
