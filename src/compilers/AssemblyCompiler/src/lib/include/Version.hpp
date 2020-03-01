/* VERSION.hpp
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 11:44:11 AM
 * Last edited:
 *   3/1/2020, 2:21:18 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Version class is meant to be an easy way of representing version
 *   numbers. It does so with three values: a major version, minor version
 *   and tiny or bugfix version. It allows easy comparison and read/write
 *   from/to all sort of streams. This particular file is the header file for
 *   Version.cpp.
**/

#ifndef VERSION_HPP
#define VERSION_HPP

#include <iostream>
#include <string>

namespace Tools {
    class Version {
        public:
            /* Major version number, i.e. the X in X.0.0 */
            char major_num;
            /* Minor version number, i.e. the X in 0.X.0 */
            char minor_num;
            /* Tiny version number, i.i. the X in 0.0.X */
            char tiny_num;

            /* Stores a version number as three parts. By default, the version is 1.0.0 */
            Version();
            /* Stores a version number as three parts. Can be compared to other versions using <, <=, ==, >= or >. */
            Version(char major_num, char minor_num, char tiny_num);

            friend std::string to_string(const Version& v);

            friend bool operator==(const Version& l, const Version& r);
            friend bool operator!=(const Version& l, const Version& r);

            friend bool operator<(const Version& l, const Version& r);
            friend bool operator>(const Version& l, const Version& r);
            friend bool operator<=(const Version& l, const Version& r);
            friend bool operator>=(const Version& l, const Version& r);

            friend std::ostream& operator<<(std::ostream& os, const Version& v);
            friend std::istream& operator>>(std::istream& os, Version& v);
    };

    /* Comparison operator for the Version class. Returns true if all three version numbers are equal. */
    bool operator==(const Version& l, const Version& r);
    /* Negated comparison operator for the Version class. Returns true if any of the version numbers differ. */
    bool operator!=(const Version& l, const Version& r);

    /* Smaller than operator for the Version class. Returns true if the left version is lower than the right. */
    bool operator<(const Version& l, const Version& r);
    /* Smaller than operator for the Version class. Returns true if the left version is higher than the right. */
    bool operator>(const Version& l, const Version& r);
    /* Smaller than operator for the Version class. Returns true if the left version is lower or equal than the right. */
    bool operator<=(const Version& l, const Version& r);
    /* Smaller than operator for the Version class. Returns true if the left version is higher or equal than the right. */
    bool operator>=(const Version& l, const Version& r);

    /* Stream write operator for the Version class. Writes a string representation of the Version number to the stream. */
    std::ostream& operator<<(std::ostream& os, const Version& v);
    /* Stream read operator for the Version class. Reads a string representation of the Version numbers from the stream. */
    std::istream& operator>>(std::istream& os, Version& v);

    /* Returns a string representation of this Version object */
    std::string to_string(const Version& v);
}

#endif