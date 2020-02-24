%{


#include <stdio.h>

extern int yylex();
static int yyerror( char *errname);

%}

%token SET ADD SUB MUL DIV SHFL SHFR SHFRA
%token MEM_READ MEM_WRITE OUT END
%token REG_VAL DEC_VAL HEX_VAL

%type <void> result

%%

result: SET
    {
        printf("test");
    }

%%

static int yyerror( char *error)
{
    printf("Error parsing source code (line %d, col %d): %s\n", line, col, error);
    return -1;
}