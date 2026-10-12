%{
  #include "yy.tab.h"
%}

%option noyywrap
%option nounput
%option noinput

%%

. { return yytext[0]; }

%%
