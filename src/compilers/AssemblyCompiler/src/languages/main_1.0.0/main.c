/* MAIN 1 0 0.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:18:03 PM
 * Last edited:
 *   3/3/2020, 8:20:11 PM
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

/* Parses given file to a list of instructions. */
struct instr_list* parse(const char* file_name) {
    // Init the instructions list
    program = MAKE_INSTR_LIST();

    // Open the input file
    yyin = fopen(file_name, "r");
    if (yyin == NULL) {
        fprintf(stderr, "\nERROR: Could not open file \"%s\": %s\n\n", file_name, strerror(errno));
        exit(-1);
    }
    // Run the parser
    yyparse();
    // Close the input again
    fclose(yyin);

    // Return the list of instructions
    return program;
}

/* Compiles an instruction to binary code */
char* compile(struct instr* i) {
    if (i->id == 0x00) {
        return SET_compile((struct SET_instr*) i);
    }

    // In theory, we should never get to this point
    return NULL;
}