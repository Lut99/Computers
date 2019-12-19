/* STRINGCONVERTER.cpp
*    by Lut99
*
*  The StringConverter is a namespace that allows conversion from string to
*  various other datatypes. In contradiction to readily made available
*  functions, the amount of forgiveness is custumizable, but is set to very
*  strict by default (NoForgiveness).
**/

#include <limits.h>
#include <iostream>
#include <sstream>

#include "StringConverter.h"

unsigned char StringConverter::toUChar(std::string to_parse, StringConverterMode mode) {

}
char StringConverter::toChar(std::string to_parse, StringConverterMode mode) {
    
}

unsigned short StringConverter::toUShort(std::string to_parse, StringConverterMode mode) {
    
}
short StringConverter::toShort(std::string to_parse, StringConverterMode mode) {
    
}

unsigned int StringConverter::toUInt(std::string to_parse, StringConverterMode mode) {
    // Preparse the string to find the actual number, as specified by the mode
    std::stringstream sstr;
    int in_stream = 0;
    bool non_num = false;
    for (int i = 0; i < to_parse.length(); i++) {
        char c = to_parse[i];
        if (c < '0' || c > '9') {
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
            }
            sstr << c;
            in_stream++;
        }
    }

    // If no number has been found, throw the appropriate exception
    if (in_stream == 0) {
        throw NoNumberException(to_parse, mode);
    }

    // Parse the actual number from left to right
    unsigned long result = 0;
    std::string num_to_parse = sstr.str();
    unsigned long times = 1;
    for (int i = 0; i < num_to_parse.length(); i++) {
        char c = num_to_parse[num_to_parse.length() - 1 - i];

        //std::cout << "Char to parse: " << c << std::endl;

        // First, check if the value of this number overflows
        if (((unsigned long)(c - '0')) > ULONG_MAX / times) {
            throw OverflowException(num_to_parse, to_parse, "unsigned long", mode);
        }

        // Compute the value of this number
        unsigned long value = ((unsigned long)(c - '0')) * times;
        //std::cout << "Value in number: " << value << std::endl;

        // Check if an overflow for result would occur
        if (result > UINT_MAX - value) {
            throw OverflowException(num_to_parse, to_parse, "uint", mode);
        }

        //std::cout << "Old result: " << result << std::endl;

        // Finally, add the value to the result
        result += value;

        //std::cout << "New result: " << c << std::endl;

        //std::cout << "-----------" << std::endl;

        // Update times
        times *= 10;
    }
    return result;
}
int StringConverter::toInt(std::string to_parse, StringConverterMode mode) {
    // Preparse the string to find the actual number, as specified by the mode
    std::stringstream sstr;
    int sign = 1;
    int in_stream = 0;
    bool non_num = false;
    for (int i = 0; i < to_parse.length(); i++) {
        char c = to_parse[i];
        if (c == '-') {
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

    // Parse the actual number from left to right
    unsigned long result = 0;
    std::string num_to_parse = sstr.str();
    unsigned long times = 1;
    for (int i = 0; i < num_to_parse.length(); i++) {
        char c = num_to_parse[num_to_parse.length() - 1 - i];

        // Compute the theoretical maximum for the div
        int ceiling = LONG_MAX / times;
        if (sign < 0) {
            LONG_MAX / (times + 1);
        }

        // First, check if the value of this number overflows
        if (((unsigned long)(c - '0')) > LONG_MAX / times) {
            throw OverflowException(num_to_parse, to_parse, "unsigned long", mode);
        }

        // Compute the value of this number
        unsigned long value = ((unsigned long)(c - '0')) * times;

        // Check if an overflow for result would occur
        if (sign > 0 && result > INT_MAX - value) {
            throw OverflowException(num_to_parse, to_parse, "int", mode);
        }
        if (sign < 0 && result > INT_MAX - value + 1) {
            throw UnderflowException("-" + num_to_parse, to_parse, "int", mode);
        }
        

        // Finally, add the value to the result
        result += value;

        // Update times
        times *= 10;
    }
    return sign * result;
}

unsigned long StringConverter::toULong(std::string to_parse, StringConverterMode mode) {
    
}
long StringConverter::toLong(std::string to_parse, StringConverterMode mode) {
    
}