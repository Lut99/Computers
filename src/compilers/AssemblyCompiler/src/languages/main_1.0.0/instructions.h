/* INSTRUCTIONS.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:56:15 PM
 * Last edited:
 *   3/4/2020, 7:50:11 PM
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
#include <stdio.h>

/* Compiles a SET instruction to binary code. */
void SET_compile(FILE* output, int variation, char reg, long reg_val);

#endif