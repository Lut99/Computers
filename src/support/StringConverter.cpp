/* STRINGCONVERTER.cpp
*    by Lut99
*
*  The StringConverter is a namespace that allows conversion from string to
*  various other datatypes. In contradiction to readily made available
*  functions, the amount of forgiveness is custumizable, but is set to very
*  strict by default (NoForgiveness).
**/

#include <iostream>
#include <sstream>
#include <map>

#include "Limits.cpp"
#include "StringConverter.h"

template <typename T> T StringConverter::toInteger(std::string to_parse, StringConverterMode mode) {
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