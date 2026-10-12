%{
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
  struct Attr {
    int pos;
    int len;
  };
%}

%define api.value.type { struct Attr }

%%

input: { $$.pos = 0; } S
       ;

S   : '(' { $$.pos = $0.pos + 1; } L ')' 
      { $$.len = $3.len + 2; }
    | 'a' 
      { 
        printf("%d\n", $0.pos); 
        $$.len = 1; 
      }
    ;

L   : L ',' { $$.pos = $0.pos + $1.len + 1; } S 
      { $$.len = $1.len + $4.len + 1; }
    | S 
      { $$.len = $1.len; }
    ;

%%

int main(void)
{
  yyparse();
}

void yyerror(char const *s)
{
  fprintf(stderr, "%s\n", s);
}
