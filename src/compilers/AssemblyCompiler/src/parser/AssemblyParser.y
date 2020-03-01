%{


#include <stdio.h>

#include "../../lib/include/Globals.h"

extern "C" int yylex();
static int yyerror( char *errname);

%}

%union {
    int     cint;
}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token REG_VAL DEC_VAL HEX_VAL

%type <cint> result

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