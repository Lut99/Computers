/* TOOLS.c
 *   by Lut99
 *
 * Created:
 *   3/2/2020, 12:53:25 PM
 * Last edited:
 *   3/3/2020, 8:18:09 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Tools.c contains helper functions that are general to nearly all
 *   Instructions sets. Examples are encoding of longs to bytes, reading a
 *   hex string or converting it to an integer value.
**/

#include <stdlib.h>

#include "Tools.h"


struct string* MAKE_STRING(char* data, int length) {
    struct string* to_ret = (struct string*) malloc(sizeof(struct string));
    to_ret->data = (char*) malloc(length * sizeof(char));
    for (int i = 0; i < length; i++) {
        to_ret->data[i] = data[i];
    }
    to_ret->length = length;
    return to_ret;
}

void FREE_STRING(struct string* s) {
    free(s->data);
    free(s);
}

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

unsigned long string_to_hex(struct string* s) {
    // The input is a hex-string, but it is assumed there is at least one and
    //   that there is no leading 0x, and there are only numbers and a-f and
    //   A-F.
    unsigned long res = 0;
    for (int i = 0; i < s->length; i++) {
        char c = s->data[s->length - 1 - i];
        int val;
        if (c >= '0' && c <= '9') {
            // Simply substract the number and add, times the place
            val = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            val = 10 + (c - 'a');
        } else {
            val = 10 + (c - 'A');
        }
        res += val * (16 * i);
    }
    return res;
}