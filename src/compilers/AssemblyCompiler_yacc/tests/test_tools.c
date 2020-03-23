/* TEST TOOLS.c
 *   by Lut99
 *
 * Created:
 *   3/4/2020, 8:44:43 PM
 * Last edited:
 *   3/4/2020, 9:15:39 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file tests the functions laid out in the test_tools file.
**/

#include <stdlib.h>
#include <stdio.h>
#include "../src/languages/Tools.h"


int test_string_to_hex(struct string* hex, unsigned long expected) {
    printf("Testing 'string_to_hex(%s)'...\n", hex->data);

    printf("  Hex value     : %s\n", hex->data);
    printf("  Expected value: %lu\n", expected);
    
    // Do the convertion
    unsigned long res = string_to_hex(hex);
    printf("  Result        : %lu\n", res);

    // Check if they equal
    if (res == expected) {
        printf("Succes\n\n");
        return 1;
    } else {
        printf("Failure\n\n");
        return 0;
    }
}


int main() {
    printf("\n*** TEST FOR TOOLS.C ***\n\n");

    struct string* s;

    s = MAKE_STRING("00", 2);
    if (!test_string_to_hex(s, 0)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("0000", 4);
    if (!test_string_to_hex(s, 0)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("00FF", 4);
    if (!test_string_to_hex(s, 255)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("FF00", 4);
    if (!test_string_to_hex(s, 65280)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("FFFF", 4);
    if (!test_string_to_hex(s, 65535)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("FFFFFFFF", 8);
    if (!test_string_to_hex(s, 4294967295)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("AE8850AA", 8);
    if (!test_string_to_hex(s, 2928169130)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("FFFFFFFF", 8);
    if (!test_string_to_hex(s, 4294967295)) {
        exit(-1);
    }
    FREE_STRING(s);

    
    s = MAKE_STRING("FFFFFFFFFFFFFFFF", 16);
    if (!test_string_to_hex(s, 18446744073709551615UL)) {
        exit(-1);
    }
    FREE_STRING(s);

    s = MAKE_STRING("FFFFFFFFFFFFFFFFF", 17);
    if (!test_string_to_hex(s, 18446744073709551615UL)) {
        exit(-1);
    }
    FREE_STRING(s);
}