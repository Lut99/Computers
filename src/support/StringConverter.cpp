/* STRINGCONVERTER.cpp
*    by Lut99
*
*  The StringConverter is a namespace that allows conversion from string to
*  various other datatypes. In contradiction to readily made available
*  functions, the amount of forgiveness is very low, and it returns different
*  exceptions based on what went wrong.
**/

#include "StringConverter.h"

unsigned char StringConverter::toUChar(std::string to_parse) {

}
char StringConverter::toChar(std::string to_parse) {
    
}

unsigned short StringConverter::toUShort(std::string to_parse) {
    
}
short StringConverter::toShort(std::string to_parse) {
    
}

unsigned int StringConverter::toUInt(std::string to_parse) {
    unsigned int result = 0;
    // Work from right to left
    for (int i = to_parse.length() - 1; i >= 0; i--) {

    }
}
int StringConverter::toInt(std::string to_parse) {
    
}

unsigned long StringConverter::toULong(std::string to_parse) {
    
}
long StringConverter::toLong(std::string to_parse) {
    
}