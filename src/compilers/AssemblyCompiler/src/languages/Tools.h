/* TOOLS.h
 *   by Lut99
 *
 * Created:
 *   3/2/2020, 12:53:37 PM
 * Last edited:
 *   3/3/2020, 7:48:48 PM
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

/* Struct for storing a string together with it's length */
struct string {
    char* data;
    int length;
};

/* Returns a newly allocated string object */
struct string* MAKE_STRING(char* data, int length);
/* Frees given string object. */
void FREE_STRING(struct string* s);

/* Converts given long to a byte array. */
void long_to_char(long number, char* result);

/* Reads a string that contains a hexidecimal number, and returns the value of that number (assumes the hexadecimal has correct structure). */
unsigned long string_to_hex(struct string* s);

#endif