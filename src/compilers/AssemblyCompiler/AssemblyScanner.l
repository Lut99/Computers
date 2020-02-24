%{
    #include <stdio.h>

    #include "AssemblyParser.tab.h"

    #define FILTER(n) \
        printf("%s\n", #n);
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

$[0-9]+                             { FILTER(REG_VAL); }
0x[0-9]+                            { FILTER(HEX_VAL); }
[0-9]+                              { FILTER(DEC_VAL); }

"//".*$                             {  }
"/*"([^*]|(\*+[^*/]))*\*+\/         {  }

\n.*                                {  }
[ \t]                               {  }
