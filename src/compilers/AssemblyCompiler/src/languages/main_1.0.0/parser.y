%{


#include <stdio.h>

#include "../../lib/include/Globals.h"

extern "C" int yylex();
static int yyerror( char *err);

%}

%union {
    int             reg_val;
    char*           hex_val;
    unsigned long   dec_val;
}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token<reg_val> REG_VAL
%token<hex_val> HEX_VAL
%token<dec_val> DEC_VAL

%type <reg_val> result

%%

result: SET
    {
        printf("test");
    }

%%

static int yyerror( char *error)
{
    printf("Error parsing source code (line %ld, col %ld): %s\n", row + (long) 1, col + (long) 1, error);
    return -1;
}