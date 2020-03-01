/* INSTRUCTIONS.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:55:54 PM
 * Last edited:
 *   3/1/2020, 3:09:50 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the compile derivatives for the instructions in
 *   this instruction set, and also convenient make functions.
**/

#include "instructions.h"

struct SET_instr* SET_make(int variation, long value) {
    struct SET_instr* to_ret = (struct SET_instr*) malloc(sizeof(struct SET_instr*));
    to_ret->id = 0x00;
    to_ret->variation = variation;
    to_ret->value = value;
    return to_ret;
}

char* SET_compile(struct SET_instr* instr) {
    // Determine the size of this instruction
    int size = 2;
    if (instr->variation == 1) {
        size = 9;
    }

    // Allocate a new array
    char* to_ret = (char*) malloc(size * sizeof(char));
    
    // Write the code first
    to_ret[0] = 0x00;
    // If there is only a char, write that and done
    if (instr->variation == 0) {
        to_ret[1] = (char) instr->value;
    } else {
        // Put the long there
        
    }
}