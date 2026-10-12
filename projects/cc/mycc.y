%{
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
  struct {
    char* type;
    char* name;
    long value;
  } symbol[100];
  int n = 0;
%}

%define api.value.type { void* }
%token ID
%token PROC
%token FUNC

%%

P:D ';' S;

D:D ';' D
| ID ':' T
| PROC ID '(' A ')' ';' D ';' S
| FUNC ID '(' A ')' ':' T ';' D ';' S
;

T:CHAR
| INTEGER
| REAL
| BOOLEAN
| ARRAY '[' NUM ']' OF T
| '^' T
| RECORD D END
;

A:%empty
| paramlist
;

paramlist:ID ':' T
| paramlist ',' ID ':' T
;

S:ID ':' '=' E
| IF E THEN S
| WHILE E DO S
| ID '(' rparam ')'
| S ';' S
;

E:LITERAL
| NUM
| NUM '.' NUM
| ID
| E '+' E
| E '*' E
| '-' E
| '(' E ')'
| ID '<' ID
| E AND E
| E MOD E
| ID '[' E ']'
| E '^'
| ID '(' rparam ')'
;

rparam: %empty
| rplist
;

rplist: rplist ',' E
| E
;

%%

int main(void)
{
  yyparse();
  printf("symbol table\n");
  printf("+-------+-------+-------+\n");
  printf("|type\t|name\t|value\t|\n");
  printf("+-------+-------+-------+\n");
  for (int i = 0; i < n; i++) {
    printf("|%s\t|%s\t|%ld\t|\n", symbol[i].type, symbol[i].name, symbol[i].value);
  }
  printf("+-------+-------+-------+\n");
}

void yyerror(char const *s)
{
  fprintf(stderr, "%s\n", s);
}
