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
    class UnderflowException : public StringConvertionException {
        public:
            const std::string num;
            const std::string type;

            /* Exception for when the to-be-parsed number causes an underflow */
            UnderflowException(const std::string num_to_parse, const std::string to_parse, const std::string type_name, const StringConverterMode forgiveness_mode)
                : StringConvertionException(to_parse, "The number \"" + num_to_parse + "\" is too small to be parsed as " + type_name, forgiveness_mode),
                num(num_to_parse),
                type(type_name)
            {}
    };

    /* Converts the value in a string to a numerical value. If it fails, an appropriate derivation of StringConvertionException is thrown. */
    template <typename T> T toInteger(std::string to_parse, StringConverterMode mode = NoForgiveness) {
        // Preparse the string to find the actual number, as specified by the mode
        std::stringstream sstr;
        int sign = 1;
        int in_stream = 0;
        bool non_num = false;
        for (int i = 0; i < to_parse.length(); i++) {
            char c = to_parse[i];
            if (std::Limits<T>::can_minus && c == '-') {
                if (in_stream > 0) {
                    // We have encountered a number before; this is illegal
                    throw IllegalCharacterException(c, to_parse, mode);
                }
                sign *= -1;
            } else if (c < '0' || c > '9') {
                if (mode == ParseFirstNumber) {
                    // If there is something in the buffer, we now have the first number and so we quit
                    if (in_stream > 0) {
                        break;
                    }
                } else if (mode == ParseLastNumber) {
                    // Set the flag that a break has happened
                    non_num = true;
                } else if (mode == AllowSpaces) {
                    if (c != ' ') {
                        throw IllegalCharacterException(c, to_parse, mode);
                    }
                } else {
                    throw IllegalCharacterException(c, to_parse, mode);
                }
            } else {
                // Clear the buffer if the non_num flag is set
                if (non_num) {
                    non_num = false;
                    sstr.str("");
                    sstr.clear();
                    in_stream = 0;
                    sign = 1;
                }
                sstr << c;
                in_stream++;
            }
        }

        // If no number has been found, throw the appropriate exception
        if (in_stream == 0) {
            throw NoNumberException(to_parse, mode);
        }

        // Ready the numbers for parsing
        T MIN = std::Limits<T>::min;
        T MAX = std::Limits<T>::max;

        T result = 0;
        T times = 1;

        std::string num_to_parse = sstr.str();
        
        // Now fetch the value
        for (int i = 0; i < num_to_parse.length(); i++) {
            char c = num_to_parse[num_to_parse.length() - 1 - i];

            // First, check if the times would overflow
            T c_val = (T) (c - '0');
            if (c_val > MAX / times) {
                std::cerr << "Overflow for times (MAX=" << MAX << ", type=" << std::Limits<T>::name << ")" << std::endl;
                throw OverflowException(num_to_parse, to_parse, std::Limits<T>::name, mode);
            }

            // Compute actual value of the number in the integer
            T value = sign * c_val * times;

            // Check if an overflow OR underflow would occur
            if (value > 0 && result > MAX - value) {
                std::cerr << "Overflow for result (MAX=" << MAX << ", type=" << std::Limits<T>::name << ")" << std::endl;
                throw OverflowException(num_to_parse, to_parse, std::Limits<T>::name, mode);
            }
            if (value < 0 && result < MIN - value) {
                throw UnderflowException("-" + num_to_parse, to_parse, std::Limits<T>::name, mode);
            }
            
            // Finally, add the value to the result
            result += value;

            // Update times, but do use overflow protection (but ignore if we are done anyway)
            if (i < num_to_parse.length() - 1 && times > MAX / 10) {
                std::cerr << "Overflow for new times (MAX=" << MAX << ", type=" << std::Limits<T>::name << ")" << std::endl;
                throw OverflowException(num_to_parse, to_parse, std::Limits<T>::name, mode);
            }
            times *= 10;
        }
        return result;
    }
}

#endif