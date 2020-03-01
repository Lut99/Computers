/* INSTRUCTIONS.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:56:15 PM
 * Last edited:
 *   3/1/2020, 3:09:48 PM
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

struct SET_instr {
    char id;
    int variation;
    long value;
};

struct SET_instr* SET_make(int variation, long value);

char* SET_compile(struct SET_instr* instr);

#endif