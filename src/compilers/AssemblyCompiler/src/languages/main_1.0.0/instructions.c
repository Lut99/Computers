/* INSTRUCTIONS.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:55:54 PM
 * Last edited:
 *   3/4/2020, 8:43:51 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the compile derivatives for the instructions in
 *   this instruction set, and also convenient make functions.
**/

#include "../Tools.h"
#include "instructions.h"


void SET_compile(FILE* output, int variation, char reg, long reg_val) {
    // Write the code first
    char c;
    c = (char) (0x00 + variation);
    fwrite(&c, sizeof(char), 1, output);
    // Add the target register
    fwrite(&reg, sizeof(char), 1, output);
    if (variation == 0) {
        // Put the long there
        char to_ret[8];
        long_to_char(reg_val, to_ret);
        fwrite(to_ret, sizeof(char), 8, output);
    } else {
        // If there is only a char, write that and done
        c = (char) (reg_val & 0xFF);
        fwrite(&c, sizeof(char), 1, output);
        printf("Value: %ld\n", reg_val);
    }
}