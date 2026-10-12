#include <stdio.h>

int power(int A, int B) {
  int res = 1;
  int factor = A;
  while (B != 0) {
    if (B & 1) {
      res *= factor;
      res %= 1000;
    }
    factor *= factor;
    factor %= 1000;
    B >>= 1;
  }
  return res;
}

int main() {
  int A, B;
  while (1) {
    scanf("%d %d", &A, &B);
    if (A == 0 && B == 0) {
      break;
    }
    printf("%d\n", power(A, B));
  }
  return 0;
}
