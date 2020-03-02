/* TOOLS.h
 *   by Lut99
 *
 * Created:
 *   3/2/2020, 12:53:37 PM
 * Last edited:
 *   3/2/2020, 12:55:56 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Tools.c contains helper functions that are general to nearly all
 *   Instructions sets. Examples are encoding of longs to bytes, reading a
 *   hex string or converting it to an integer value.
**/

#ifndef TOOLS_H
#define TOOLS_H

/* Converts given long to a byte array. */
void long_to_char(long number, char* result);

/* Reads a string that contains a hexidecimal number, and returns the value of that number (assumes the hexadecimal has correct structure). */
long string_to_hex(char* hex_str);

#endif