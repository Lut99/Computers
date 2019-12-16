/* STRINGCONVERTER.h
*    by Lut99
*
*  Header file for StringConverter.cpp.
**/

#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include <exception>

namespace StringConverter {
    class StringConvertionException : std::exception {
        public:
            const std::string str;
            const std::string msg;

            /* StringConvertion Base error */
            StringConvertionException(const std::string to_parse, const std::string message)
                : str(to_parse),
                msg(message)
            {}
    };

    /* Converts the value in a string to an unsigned char. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned char toUChar(std::string to_parse);
    /* Converts the value in a string to a signed char. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    char toChar(std::string to_parse);
    /* Converts the value in a string to an unsigned short. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned short toUShort(std::string to_parse);
    /* Converts the value in a string to a signed short. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    short toShort(std::string to_parse);
    /* Converts the value in a string to an unsigned int. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned int toUInt(std::string to_parse);
    /* Converts the value in a string to a signed int. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    int toInt(std::string to_parse);
    /* Converts the value in a string to an unsigned long. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned long toULong(std::string to_parse);
    /* Converts the value in a string to a signed long. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    long toLong(std::string to_parse);
}

#endif