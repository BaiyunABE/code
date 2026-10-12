#include <stdio.h>

int main() {
  int cnt = 0;
  int sp = 0;
  char c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (c == '(') {
      sp++;
      cnt++;
    } else if (c == ')') {
      if (sp == 0) {
        printf("-1\n");
        return 0;
      }
      else {
        sp--;
      }
    } else {
      printf("0\n");
      return 0;
    }
  }
  if (sp == 0) {
    printf("%d\n", cnt);
  }
  else {
    printf("-1\n");
  }
  return 0;
}
