/* INSTRUCTIONS.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:56:15 PM
 * Last edited:
 *   3/2/2020, 12:51:18 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains the compile derivatives for the instructions in
 *   this instruction set, and also convenient make functions.
**/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>

/* SET instruction: sets the value of a register to that of a constant or register. */
struct SET_instr {
    char id;
    int variation;
    char t_reg;
    long value;
};
/* Fills a SET_instr struct and returns the newly allocated result */
struct SET_instr* SET_make(int variation, char reg, long value);
/* Compiles a SET instruction to binary code. */
char* SET_compile(struct SET_instr* instr);

#endif