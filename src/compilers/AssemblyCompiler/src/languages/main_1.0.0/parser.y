%{


#include <stdio.h>

#include "../instructions.h"
#include "../globals.h"
#include "../../Tools.h"

extern int yylex();
static int yyerror( char *err);

extern FILE* yyin;
FILE* out;

%}

%union {
    int                 reg_val;
    struct string*      hex_val;
    unsigned long       value;
    struct instr_list*  instruction_list;
    struct instr*       instruction;
}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token<reg_val> REG_VAL
%token<hex_val> HEX_VAL
%token<value> DEC_VAL

%nterm start instrs instr set_instr
%type<value> value

%start start

%%

start: instrs
    ;

instrs: instr instrs
    | instr
    ;

instr: set_instr
    ;

set_instr: SET REG_VAL value
        {
            SET_compile(out, 0, (char) $2, $3);
        }
    | SET REG_VAL REG_VAL
        {
            SET_compile(out, 1, (char) $2, $3);
        }
    ;

value: HEX_VAL
        {
            printf("%s %i\n", $1->data, $1->length);
            $$ = string_to_hex($1);
            printf("%lu\n", $$);
            // Don't forget to deallocate the object
            FREE_STRING($1);
        }
    | DEC_VAL
        {
            $$ = $1;
        }
    ;

%%

static int yyerror( char *error)
{
    printf("Error parsing source code (line %ld, col %ld): %s\n", row + (long) 1, col + (long) 1, error);
    return -1;
}

void set_yyin(FILE* target) {
    yyin = target;
}
void set_out(FILE* target) {
    out = target;
}