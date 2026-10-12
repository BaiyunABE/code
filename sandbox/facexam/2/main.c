#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);
  int* a = (int*)malloc((n + 1) * sizeof(int));
  if (!a) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = n; i > 1; i--) {
    for (int j = 1; j <= n; j++)
      printf("%d", a[j]);
    printf("\n");
    if (a[i] > a[i / 2]) {
      a[0] = a[i];
      a[i] = a[i / 2];
      a[i / 2] = a[0];
    }
  }
  for (int i = n; i > 0; i--) {
    for (int j = 1; j <= i; j++)
      printf("%d", a[j]);
    printf("\n");
    a[1] = a[i];
    for (int j = 2; j < i; j *= 2) {
      if (a[j] < a[j + 1]) {
        j++;
      }
      a[0] = a[j / 2];
      a[j / 2] = a[j];
      a[j] = a[0];
    }
  }
  return EXIT_SUCCESS;
}
