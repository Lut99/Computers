%{


#include <stdio.h>

#include "../instructions.h"
#include "../globals.h"

extern "C" int yylex();
static int yyerror( char *err);

%}

%union {
    int                 reg_val;
    char*               hex_val;
    unsigned long       dec_val;
    struct instr_list*  program;
    struct instr*       instruction;
}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token<reg_val> REG_VAL
%token<hex_val> HEX_VAL
%token<dec_val> DEC_VAL

%type<program> start instrs
%type<instruction> instr set_instr

%start start

%%

start: instrs
        {
            $$ = $1;
        }
    ;

instrs: instrs instr
    | instr
    ;

instr: set_instr
        {
            $$ = $1
        }
    ;

set_instr: SET REG_VAL HEX_VAL
        {
            $$ = SET_make(0, (char) $2, readHex($3));
        }
    | SET REG_VAL DEC_VAL
        {
            $$ = SET_make(0, (char) $2, $3);
        }
    | SET REG_VAL REG_VAL
        {
            $$ = SET_make(1, (char) $2, $3);
        }
    ;

%%

static int yyerror( char *error)
{
    printf("Error parsing source code (line %ld, col %ld): %s\n", row + (long) 1, col + (long) 1, error);
    return -1;
}