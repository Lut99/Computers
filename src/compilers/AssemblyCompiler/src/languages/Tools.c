/* TOOLS.c
 *   by Lut99
 *
 * Created:
 *   3/2/2020, 12:53:25 PM
 * Last edited:
 *   3/6/2020, 2:25:48 PM
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

unsigned long string_to_hex(struct string* s) {
    // The input is a hex-string, but it is assumed there is at least one and
    //   that there is no leading 0x, and there are only numbers and a-f and
    //   A-F.
    unsigned long res = 0;
    unsigned long added = 1;
    for (int i = 0; i < s->length; i++) {
        char c = s->data[s->length - 1 - i];
        unsigned long val;
        if (c >= '0' && c <= '9') {
            // Simply substract the number and add, times the place
            val = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            val = 10 + (c - 'a');
        } else {
            val = 10 + (c - 'A');
        }
        res += val * added;

        added *= 16;
    }
    return res;
}