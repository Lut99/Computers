/* INSTR BASE.h
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 1:08:15 PM
 * Last edited:
 *   3/1/2020, 3:02:16 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The InstrBase file contains the baseclass for an instruction set.
 *   Additionally, it contains C-code for an InstructionSet class, which is
 *   filled in by the Parser. This particular file is the header file  for
 *   InstrBase.c.
**/

#ifndef INSTRBASE_H
#define INSTRBASE_H

// If compiled with C++ compiler, make sure there isn't any name mangling
#include <stdlib.h>

/* Base class for all instructions */
struct instr {
    char id;
};

/* List of instructions that will be written to file */
struct instr_list {
    struct instr** items;
    unsigned long len;
    unsigned long max_len;
};

/* Creates an empty instruction list. */
struct instr_list* MAKE_INSTR_LIST();
/* Frees an instruction list and all instructions therein. */
void FREE_INSTR_LIST(struct instr_list* list);

/* Appends a new instruction to the list of instructions. */
void append_instr(struct instr_list* list, struct instr* to_add);

#endif