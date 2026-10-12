#include <stdio.h>

int init() {
  return 10;
}

int a = init();

int main() {
  printf("a = %d\n", a);
  return 0;
}

