/* INSTR BASE.c
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 1:07:14 PM
 * Last edited:
 *   3/3/2020, 8:18:13 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The InstrBase file contains the baseclass for an instruction set.
 *   Additionally, it contains C-code for an InstructionSet class, which is
 *   filled in by the Parser. This particular file is the implementation file
 *   for InstrBase.h.
**/

#include "InstrBase.h"


struct instr_list* MAKE_INSTR_LIST() {
    struct instr_list* to_ret = (struct instr_list*) malloc(sizeof(struct instr_list));
    to_ret->len = 0;
    to_ret->max_len = 50;
    to_ret->items = (struct instr**) malloc(to_ret->max_len * sizeof(struct instr*));
    return to_ret;
}

void FREE_INSTR_LIST(struct instr_list* list) {
    for (unsigned long i = 0; i < list->len; i++) {
        free(list->items[i]);
    }
    free(list->items);
    free(list);
}

void append_instr(struct instr_list* list, struct instr* to_add) {
    // Check if we have space to add it
    if (list->len >= list->max_len) {
        // Increase the max size with another 50
        unsigned long new_max_len = list->max_len + 50;
        struct instr** new_items = (struct instr**) malloc(new_max_len * sizeof(struct instr*));
        for (unsigned long i = 0; i < list->max_len; i++) {
            new_items[i] = list->items[i];
        }
        free(list->items);
        list->items = new_items;
        list->max_len = new_max_len;
    }

    // Add the element at the end of the list
    list->items[list->len] = to_add;
    list->len++;
}

