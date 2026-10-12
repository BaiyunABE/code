%{
  #include "mycc.tab.h"
%}

%option noyywrap
%option nounput
%option noinput

%%

[ \t\n] { /* empty */  }

"procedure" { return PROC; }

"function" { return FUNC; }

[a-zA-Z][a-zA-Z0-9]* {
  yylval = (YYSTYPE)strndup(yytext, yyleng);
  return ID;
}


[0-9]+ { 
  yylval = (YYSTYPE)(long)atoi(yytext);
  return NUM;
}

. { return yytext[0]; }

%%
