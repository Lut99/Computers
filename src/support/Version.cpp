/* VERSION.cpp
*    by Lut99
*
*  Simple version class that stores three version numbers and can be easily
*  compared to another one.
**/

#include "Version.h"

Computer::Version::Version(char major, char minor, char tiny)
    : major(major),
    minor(minor),
    tiny(tiny)
{}

inline bool Computer::operator==(const Computer::Version& lhs, const Computer::Version& rhs) {
    // Check if all are equal
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.tiny == rhs.tiny;
}
inline bool Computer::operator!=(const Computer::Version& lhs, const Computer::Version &rhs) {
    return !(lhs == rhs);
}

bool Computer::operator<(const Computer::Version& lhs, const Computer::Version& rhs) {
    // Match up to where it goes correctly
    if (lhs.major != rhs.major) { return lhs.major < rhs.major; }
    if (lhs.minor != rhs.minor) { return lhs.minor < rhs.minor; }
    if (lhs.tiny != lhs.tiny) { return lhs.tiny < rhs.tiny; }
    return false;
}
inline bool Computer::operator>(const Computer::Version& lhs, const Computer::Version& rhs) {
    return rhs < lhs;
}
inline bool Computer::operator<=(const Computer::Version& lhs, const Computer::Version& rhs) {
    return !(lhs > rhs);
}
inline bool Computer::operator>=(const Computer::Version& lhs, const Computer::Version& rhs) {
    return !(lhs < rhs);
}