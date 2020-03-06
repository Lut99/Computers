/* INSTRUCTIONS.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:55:54 PM
 * Last edited:
 *   3/6/2020, 2:41:29 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the compile derivatives for the instructions in
 *   this instruction set, and also convenient make functions.
**/

#include "../Tools.h"
#include "instructions.h"


void SET_compile(FILE* output, int variation, unsigned char reg, unsigned long reg_val) {
    // Write the code first
    unsigned char c;
    c = (unsigned char) (0x00 + variation);
    fwrite(&c, sizeof(unsigned char), 1, output);
    // Add the target register
    fwrite(&reg, sizeof(unsigned char), 1, output);
    if (variation == 0) {
        // Put the long there
        fwrite(&reg_val, sizeof(unsigned long), 1, output);
    } else {
        // If there is only a char, write that and done
        c = (unsigned char) (reg_val & 0xFF);
        fwrite(&c, sizeof(unsigned char), 1, output);
    }
}

void ADD_compile(FILE* output, int variation, unsigned char reg, unsigned long reg_val_1, unsigned long reg_val_2) {
    // Write the code first
    unsigned char c;
    c = (unsigned char) (0x02 + variation);
    fwrite(&c, sizeof(unsigned char), 1, output);
    // Add the target register
    fwrite(&reg, sizeof(unsigned char), 1, output);
    // Switch the variations:
    switch(variation) {
        case 0:
            fwrite(&reg_val_1, sizeof(unsigned long), 1, output);
            fwrite(&reg_val_2, sizeof(unsigned long), 1, output);
            break;
        case 1:
            c = (unsigned char) (reg_val_1 & 0xFF);
            fwrite(&c, sizeof(unsigned char), 1, output);
            fwrite(&reg_val_2, sizeof(unsigned long), 1, output);
            break;
        case 2:
            fwrite(&reg_val_1, sizeof(unsigned long), 1, output);
            c = (unsigned char) (reg_val_2 & 0xFF);
            fwrite(&c, sizeof(unsigned char), 1, output);
            break;
        case 3:
            c = (unsigned char) (reg_val_1 & 0xFF);
            fwrite(&c, sizeof(unsigned char), 1, output);
            c = (unsigned char) (reg_val_2 & 0xFF);
            fwrite(&c, sizeof(unsigned char), 1, output);
            break;
        default:
            // Should never reach
            break;
    }
}