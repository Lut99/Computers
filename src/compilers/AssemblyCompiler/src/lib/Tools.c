/* TOOLS.c
 *   by Lut99
 *
 * Created:
 *   3/2/2020, 12:53:25 PM
 * Last edited:
 *   3/2/2020, 12:57:55 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Tools.c contains helper functions that are general to nearly all
 *   Instructions sets. Examples are encoding of longs to bytes, reading a
 *   hex string or converting it to an integer value.
**/

#include "include/Tools.h"


void long_to_char(long number, char* result) {
    unsigned char *uresult = (unsigned char*) result;
    uresult[0] = (number >> 56) & 0xFF;
    uresult[1] = (number >> 48) & 0xFF;
    uresult[2] = (number >> 40) & 0xFF;
    uresult[3] = (number >> 32) & 0xFF;
    uresult[4] = (number >> 24) & 0xFF;
    uresult[5] = (number >> 16) & 0xFF;
    uresult[6] = (number >> 8) & 0xFF;
    uresult[7] = number & 0xFF;
}

long string_to_hex(char* hex_str) {
    
}