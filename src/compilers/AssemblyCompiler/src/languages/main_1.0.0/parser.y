%{


#include <stdio.h>

#include "../instructions.h"
#include "../globals.h"
#include "../../../lib/include/Tools.h"

extern int yylex();
static int yyerror( char *err);

%}

%union {
    int                 reg_val;
    char*               hex_val;
    long                value;
    struct instr_list*  instruction_list;
    struct instr*       instruction;
}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token<reg_val> REG_VAL
%token<hex_val> HEX_VAL
%token<value> DEC_VAL

%type<instruction_list> start instrs
%type<instruction> instr set_instr
%type<value> value

%start start

%%

start: instrs
    ;

instrs: instrs instr
        {
            append_instr(program, $2);
        }
    | instr
        {
            append_instr(program, $1);
        }
    ;

instr: set_instr
        {
            $$ = $1;
        }
    ;

set_instr: SET REG_VAL value
        {
            $$ = SET_make(0, (char) $2, $3);
        }
    | SET REG_VAL REG_VAL
        {
            $$ = SET_make(1, (char) $2, $3);
        }
    ;

value: HEX_VAL
        {
            $$ = string_to_hex($1);
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