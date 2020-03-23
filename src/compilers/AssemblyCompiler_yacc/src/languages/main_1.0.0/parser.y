%{


#include <stdio.h>

#include "../instructions.h"
#include "../../Globals.h"
#include "../../Tools.h"

extern int yylex();
static int yyerror( char *err);

extern FILE* yyin;
FILE* out;

%}

%union {
    unsigned int        reg_val;
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

%nterm start instrs instr set_instr add_instr
%type<value> value
%type<reg_val> reg_val;

%start start

%%

start: instrs
    ;

instrs: instr instrs
    | instr
    ;

instr: set_instr
    | add_instr
    ;

set_instr: SET reg_val value
        {
            SET_compile(out, 0, (unsigned char) $2, $3);
        }
    | SET reg_val reg_val
        {
            SET_compile(out, 1, (unsigned char) $2, $3);
        }
    ;

add_instr: ADD reg_val value value
        {
            ADD_compile(out, 0, (unsigned char) $2, $3, $4);
        }
    | ADD reg_val reg_val value
        {
            ADD_compile(out, 1, (unsigned char) $2, $3, $4);
        }
    | ADD reg_val value reg_val
        {
            ADD_compile(out, 2, (unsigned char) $2, $3, $4);
        }
    | ADD reg_val reg_val reg_val
        {
            ADD_compile(out, 3, (unsigned char) $2, $3, $4);
        }
    ;

value: HEX_VAL
        {
            if ($1->length > 16) {
                yyerror("hex overflow");
                YYERROR;
            }
            $$ = string_to_hex($1);
            // Don't forget to deallocate the object
            FREE_STRING($1);
        }
    | DEC_VAL
        {
            $$ = $1;
        }
    ;

reg_val: REG_VAL
    {
        if ($1 > 15) {
            yyerror("too high register (max 15)");
            YYERROR;
        }
        $$ = $1;
    }

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