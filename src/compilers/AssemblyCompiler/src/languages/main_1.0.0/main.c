/* MAIN 1 0 0.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:18:03 PM
 * Last edited:
 *   3/3/2020, 9:02:44 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file describes how to compile the Chaos v1.0.0 Instruction Set
 *   from assembly to binary. Note that the syntax is the same for each
 *   instruction set, so some parsing will have to be done here.
**/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "parser/parser.tab.h"
#include "globals.h"
#include "instructions.h"
#include "../InstrBase.h"


extern FILE* yyin;

/* Compiles an instruction to binary code */
void compile(const char* input, const char* output) {
    // Init the instructions list
    program = MAKE_INSTR_LIST();

    for (int i = 0; i < program->len; i++) {
        struct instr* ins = program->items[i];
        if (ins->id == 0x00) {
            SET_compile(ins);
        }
    }
}