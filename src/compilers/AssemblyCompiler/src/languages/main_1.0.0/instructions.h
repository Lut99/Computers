/* INSTRUCTIONS.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:56:15 PM
 * Last edited:
 *   3/6/2020, 2:36:42 PM
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
void SET_compile(FILE* output, int variation, unsigned char reg, unsigned long reg_val);

/* Compiles an ADD instruction to binary code. */
void ADD_compile(FILE* output, int variation, unsigned char reg, unsigned long reg_val_1, unsigned long reg_val_2);

#endif