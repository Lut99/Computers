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
    /* The flexibility of the parser. The first mode means that it exceptions on anything else than the ten decimals, the mode 'AllowSpaces' also allows for spaces, while the other two modes discard all non-numerical characters until a number is found, parse that number and return it. This is the most flexible mode. */
    enum StringConverterMode {
        NoForgiveness,
        AllowSpaces,
        ParseFirstNumber,
        ParseLastNumber
    };
    /* Converts a StringConverterMode enum to their text representative */
    static std::string StringConverterModeToText[] = {
        "NoForgiveness",
        "AllowSpaces",
        "ParseFirstNumber",
        "ParseLastNumber"
    };

    class StringConvertionException : public std::exception {
        public:
            const std::string str;
            const std::string msg;
            const StringConverterMode mode;
            const std::string mode_name;

            /* StringConvertion Base error */
            StringConvertionException(const std::string to_parse, const std::string message, const StringConverterMode forgiveness_mode)
                : str(to_parse),
                msg(message),
                mode(forgiveness_mode),
                mode_name(StringConverterModeToText[forgiveness_mode])
            {}
    };
    class IllegalCharacterException : public StringConvertionException {
        private:
            const std::string create_msg(const char character, const std::string to_parse) const {
                std::string msg;
                msg += "Invalid '";
                msg += character;
                msg += "' character encountered in string: \"";
                msg += to_parse;
                msg += "\"";
                return msg;
            }
        public:
            const char chr;

            /* Exception for when the mode is too strict and an illegal character has been found. */
            IllegalCharacterException(const char character, const std::string to_parse, const StringConverterMode forgiveness_mode)
                : StringConvertionException(to_parse, create_msg(character, to_parse), forgiveness_mode),
                chr(character)
            {}
    };
    class NoNumberException : public StringConvertionException {
        public:
            /* Exception for when no numeric character has been found in the string (either empty string or when mode is ParseFirstNumber or ParseLastNumber) */
            NoNumberException(const std::string to_parse, const StringConverterMode forgiveness_mode)
                : StringConvertionException(to_parse, "No numbers found in: \"" + to_parse + "\"", forgiveness_mode)
            {}
    };
    class OverflowException : public StringConvertionException {
        public:
            const std::string num;
            const std::string type;
        
            /* Exception for when the to-be-parsed number causes an overflow. */
            OverflowException(const std::string num_to_parse, const std::string to_parse, const std::string type_name, const StringConverterMode forgiveness_mode)
                : StringConvertionException(to_parse, "The number \"" + num_to_parse + "\" is too large to be parsed as " + type_name, forgiveness_mode),
                num(num_to_parse),
                type(type_name)
            {}
    };

    /* Converts the value in a string to an unsigned char. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned char toUChar(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to a signed char. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    char toChar(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to an unsigned short. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned short toUShort(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to a signed short. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    short toShort(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to an unsigned int. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned int toUInt(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to a signed int. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    int toInt(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to an unsigned long. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    unsigned long toULong(std::string to_parse, StringConverterMode mode = NoForgiveness);
    /* Converts the value in a string to a signed long. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    long toLong(std::string to_parse, StringConverterMode mode = NoForgiveness);
}

#endif