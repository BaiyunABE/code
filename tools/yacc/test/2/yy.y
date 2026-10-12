%{
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
  struct Attr {
    int dpt;
    int pos;
    int len;
    int isz;
  };
%}

%define api.value.type { struct Attr }

%%

S:
  { $$.isz = 1; $$.dpt = 0; } L '.'
  { $$.isz = 0; $$.dpt = 0; } L
| { $$.isz = 1; $$.dpt = 0; } L
;

L:
  { $$.isz = $0.isz; $$.dpt = $0.dpt + 1; } L
  { $$.isz = $0.isz; $$.dpt = $0.dpt; $$.pos = $2.len; } B
  { $$.len = $2.len + 1; }
| { $$.isz = $0.isz; $$.dpt = $0.dpt; $$.pos = 0; } B
  { $$.len = 1; }
;

B:
  '0'
| '1' {
    if ($0.isz == 1) {
      printf("2^%d\n", $0.dpt);
    } else {
      printf("1/2^%d\n", $0.pos + 1);
    }
  }
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
