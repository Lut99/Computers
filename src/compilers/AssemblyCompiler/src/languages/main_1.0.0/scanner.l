%{
    #include <stdio.h>

    #include "../../lib/include/Globals.h"

    #define FILTER(n) \
        col += yyleng; \
        return n;
    
    #define LINEBUF_SIZE 256
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    FILE* yyin;
%}

%%

"SET"                               { FILTER(SET); }
"ADD"                               { FILTER(ADD); }
"SUB"                               { FILTER(SUB); }
"MUL"                               { FILTER(MUL); }
"DIV"                               { FILTER(DIV); }
"SHFL"                              { FILTER(SHFL); }
"SHFR"                              { FILTER(SHFR); }
"SHFRA"                             { FILTER(SHFRA); }
"MEM_READ"                          { FILTER(MEM_READ); }
"MEM_WRITE"                         { FILTER(MEM_WRITE); }
"OUT"                               { FILTER(OUT); }
"END"                               { FILTER(END); }

$[0-9]+                             { yyval = atoi(yytext+1);
                                      FILTER(REG_VAL); }
0x[0-9]+                            { yyval = atoi(yytext+2);
                                      FILTER(HEX_VAL); }
[0-9]+                              { yyval = atoi(yytext);
                                      FILTER(DEC_VAL); }

"//".*$                             { col = 0;
                                      row++;
                                    }
"/*"([^*]|(\*+[^*/]))*\*+\/         { for (int i = 0; i < yyleng; i++) {
                                          char c = yytext[i];
                                          if (c == '\n') {
                                              row++;
                                              col = 0;
                                          } else {
                                              col++;
                                          }
                                      }
                                    }

\n.*                                { row ++;
                                      col = 0;
                                      yyless(1);
                                    }
[ \t]                               { col += yyleng; }
