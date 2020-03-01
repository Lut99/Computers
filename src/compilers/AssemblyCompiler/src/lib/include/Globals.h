/* GLOBALS.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 12:59:17 PM
 * Last edited:
 *   3/1/2020, 2:41:45 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains globals that are needed between the scanner, parser
 *   and main function.
**/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "Instructions.h"

// Define row / columns
__attribute__((unused)) static int row = 0;
__attribute__((unused)) static int col = 0;

// Define the parse and the make functions
typedef struct instr* (*make_instr_t)(char);
typedef char* (*compile_instr_t)(struct instr*);
__attribute__((unused)) static make_instr_t make_instr;
__attribute__((unused)) static compile_instr_t compile_instr;

#endif