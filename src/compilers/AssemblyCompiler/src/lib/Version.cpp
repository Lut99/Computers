/* VERSION.cpp
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 11:45:27 AM
 * Last edited:
 *   3/3/2020, 7:32:28 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Version class is meant to be an easy way of representing version
 *   numbers. It does so with three values: a major version, minor version
 *   and tiny or bugfix version. It allows easy comparison and read/write
 *   from/to all sort of streams. This particular file is the
 *   implementation file for Version.hpp.
**/

#include <stdexcept>

#include "include/Version.hpp"

using namespace std;
using namespace Tools;

Version::Version()
    : major_num(1),
    minor_num(0),
    tiny_num(0)
{}
Version::Version(char major_num, char minor_num, char tiny_num)
    : major_num(major_num),
    minor_num(minor_num),
    tiny_num(tiny_num)
{}

inline bool Tools::operator==(const Version& lhs, const Version& rhs) {
    // Check if all are equal
    return lhs.major_num == rhs.major_num && lhs.minor_num == rhs.minor_num && lhs.tiny_num == rhs.tiny_num;
}
inline bool Tools::operator!=(const Version& lhs, const Version &rhs) {
    return !(lhs == rhs);
}

bool Tools::operator<(const Version& lhs, const Version& rhs) {
    // Match up to where it goes correctly
    if (lhs.major_num != rhs.major_num) { return lhs.major_num < rhs.major_num; }
    if (lhs.minor_num != rhs.minor_num) { return lhs.minor_num < rhs.minor_num; }
    if (lhs.tiny_num != rhs.tiny_num) { return lhs.tiny_num < rhs.tiny_num; }
    return false;
}
inline bool Tools::operator>(const Version& lhs, const Version& rhs) {
    return rhs < lhs;
}
inline bool Tools::operator<=(const Version& lhs, const Version& rhs) {
    return !(lhs > rhs);
}
inline bool Tools::operator>=(const Version& lhs, const Version& rhs) {
    return !(lhs < rhs);
}

ostream& Tools::operator<<(ostream& os, const Version& v) {
    os << to_string(v);
    return os;
}
istream& Tools::operator>>(istream& is, Version& v) {
    char c;
    int ma, mi, ti;

    // Check if not eof
    if (is.eof()) {
        return is;
    }

    // Try to read the first number
    if (!(is >> ma)) {
        return is;
    }

    // Try to find a first .
    is >> c;
    if (c != '.') {
        is.setstate(ios::failbit);
        return is;
    }

    // Try to read the second number
    if (!(is >> mi)) {
        return is;
    }

    // Try to find a second .
    is >> c;
    if (c != '.') {
        is.setstate(ios::failbit);
        return is;
    }

    // Try to read the last number
    if (!(is >> ti)) {
        return is;
    }

    // Construct an object out of it
    v.major_num = ma;
    v.minor_num = mi;
    v.tiny_num = ti;

    return is;
}

std::string Tools::to_string(const Version& v) {
    return (std::to_string(v.major_num) + "." + std::to_string(v.minor_num) + "." + std::to_string(v.tiny_num));
}