#include "FileSize.h"

FileSize::FileSize() : sizeInKB(0.0) {}

FileSize::FileSize(double kb) : sizeInKB(kb) {}

double FileSize::getSize() const { return sizeInKB; }

// Object + Object
FileSize FileSize::operator+(const FileSize& other) const {
    return FileSize(sizeInKB + other.sizeInKB);
}

// Object + Value
FileSize FileSize::operator+(double extraKB) const {
    return FileSize(sizeInKB + extraKB);
}

FileSize& FileSize::operator+=(const FileSize& other) {
    sizeInKB += other.sizeInKB;
    return *this;
}

bool FileSize::operator==(const FileSize& other) const { return sizeInKB == other.sizeInKB; }
bool FileSize::operator!=(const FileSize& other) const { return !(*this == other); }
bool FileSize::operator>(const FileSize& other) const { return sizeInKB > other.sizeInKB; }
bool FileSize::operator<(const FileSize& other) const { return sizeInKB < other.sizeInKB; }

std::ostream& operator<<(std::ostream& out, const FileSize& fs) {
    out << fs.sizeInKB << " KB";
    return out;
}

std::istream& operator>>(std::istream& in, FileSize& fs) {
    double kb;
    in >> kb;
    fs.sizeInKB = kb;
    return in;
}
