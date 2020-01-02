/* LIMITS.h
*    by Lut99
*
*  A file that can dynamically return the maximum and minimum values for given
*  integer types. Note that, for functionality, there is no .h file as this has
*  to be included.
**/

#ifndef LIMITS_H
#define LIMITS_H

#include <string>
#include <limits.h>

namespace std {
    /* The Limits template class. Returns some basic data (most notably the maximum and minimum) values of a given integral type. */
    template <class T> class Limits {
        public:
            /* By default, returns a -1 due that the type is unknown. */
            const static T min = -1;
            /* By default, returns a -1 due that the type is unknown. */
            const static T max = -1;
            /* By default, returns empty due to the fact that the type is unknown. */
            inline const static std::string name = "";
            /* By default, returns true bc unknown types can probably accept minus right? */
            const static bool can_minus = true;
    };
    /* Limits template for unsigned char. Returns a minimum of 0 and a maximum of 255. */
    template <> class Limits<unsigned char> {
        public:
            const static unsigned char min = 0;
            const static unsigned char max = UCHAR_MAX;
            inline const static std::string name = "unsigned char";
            const static bool can_minus = false;
    };
    /* Limits template for signed char. Returns a minimum of -128 and a maximum of 127. */
    template <> class Limits<signed char> {
        public:
            const static signed char min = SCHAR_MIN;
            const static signed char max = SCHAR_MAX;
            inline const static std::string name = "signed char";
            const static bool can_minus = true;
    };
    /* Limits template for char. Returns a minimum and maximum depending on the default type. */
    template <> class Limits<char> {
        public:
            const static char min = CHAR_MIN;
            const static char max = CHAR_MAX;
            inline const static std::string name = "char";
            const static bool can_minus = true;
    };
    /* Limits template for unsigned short. Returns a minimum of 0 and a maximum of USHRT_MAX. */
    template <> class Limits<unsigned short> {
        public:
            const static unsigned short min = 0;
            const static unsigned short max = USHRT_MAX;
            inline const static std::string name = "unsigned short";
            const static bool can_minus = false;
    };
    /* Limits template for short. Returns a minimum of SHRT_MIN and a maximum of SHRT_MAX. */
    template <> class Limits<short> {
        public:
            const static short min = SHRT_MIN;
            const static short max = SHRT_MAX;
            inline const static std::string name = "short";
            const static bool can_minus = true;
    };
    /* Limits template for unsigned int. Returns a minimum of 0 and a maximum of UINT_MAX. */
    template <> class Limits<unsigned int> {
        public:
            const static unsigned int min = 0;
            const static unsigned int max = UINT_MAX;
            inline const static std::string name = "unsigned int";
            const static bool can_minus = false;
    };
    /* Limits template for int. Returns a minimum of INT_MIN and a maximum of INT_MAX. */
    template <> class Limits<int> {
        public:
            const static int min = INT_MIN;
            const static int max = INT_MAX;
            inline const static std::string name = "int";
            const static bool can_minus = true;
    };
    /* Limits template for unsigned long. Returns a minimum of 0 and a maximum of ULONG_MAX. */
    template <> class Limits<unsigned long> {
        public:
            const static unsigned long min = 0;
            const static unsigned long max = USHRT_MAX;
            inline const static std::string name = "unsigned long";
            const static bool can_minus = false;
    };
    /* Limits template for long. Returns a minimum of LONG_MIN and a maximum of LONG_MAX. */
    template <> class Limits<long> {
        public:
            const static long min = LONG_MIN;
            const static long max = LONG_MAX;
            inline const static std::string name = "long";
            const static bool can_minus = true;
    };
}

#endif