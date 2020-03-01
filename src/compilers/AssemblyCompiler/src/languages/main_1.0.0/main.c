/* MAIN 1 0 0.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 2:18:03 PM
 * Last edited:
 *   3/1/2020, 3:02:25 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file describes how to compile the Chaos v1.0.0 Instruction Set
 *   from assembly to binary. Note that the syntax is the same for each
 *   instruction set, so some parsing will have to be done here.
**/

#include <stdlib.h>

#include "parser.tab.h"
#include "globals.h"
#include "instructions.h"
#include "../../lib/include/InstrBase.h"

/* Parses given file to a list of instructions. */
struct instr_list* parse(char* file_name) {
    // Init the instructions list
    program = MAKE_INSTR_LIST();

    // Open the input file
    yyin = fopen(input.c_str(), "r");
    if (yyin == NULL) {
        cerr << endl << "ERROR: Could not open file \"" + input + "\": " << strerror(errno) << endl << endl;
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