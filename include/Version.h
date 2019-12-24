/* VERSION.cpp
*    by Lut99
*
*  Simple version class that stores three version numbers and can be easily
*  compared to another one.
**/

#ifndef VERSION_H
#define VERSION_H

namespace Computer {
    class Version {
        public:
            /* Major version number, i.e. the X in X.0.0 */
            const char major;
            /* Minor version number, i.e. the X in 0.X.0 */
            const char minor;
            /* Tiny version number, i.i. the X in 0.0.X */
            const char tiny;

            /* Stores a version number as three parts. Can be compared to other versions using <, <=, ==, >= or >. */
            Version(char major, char minor, char tiny);

            friend bool operator==(const Version& l, const Version& r);
            friend bool operator!=(const Version& l, const Version& r);

            friend bool operator<(const Version& l, const Version& r);
            friend bool operator>(const Version& l, const Version& r);
            friend bool operator<=(const Version& l, const Version& r);
            friend bool operator>=(const Version& l, const Version& r);
    };
}

#endif