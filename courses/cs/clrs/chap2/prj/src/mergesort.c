#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int* A, int left, int mid, int right)
{
  // merge [left, mid) and [mid, right)
  int n1 = mid - left;
  int n2 = right - mid;
  
  int* L = malloc((n1 + 1) * sizeof(int));
  int* R = malloc((n2 + 1) * sizeof(int));
  if (L == NULL || R == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < n1; i++) {
    L[i] = A[left + i];
  }
  
  L[n1] = INT_MAX;
  
  for (int j = 0; j < n2; j++) {
    R[j] = A[mid + j];
  }
  
  R[n2] = INT_MAX;
  
  int i = 0;
  int j = 0;
  
  for (int k = left; k < right; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
  
  free(L);
  free(R);
}

void mergesort(int* A, int n)
{
  for (int len = 1; len < n; len *= 2) {
    for (int mid = len; mid < n; mid += len * 2) {
      int left = mid - len;
      int right = mid + len < n ? mid + len : n;
      merge(A, left, mid, right);
    }
  }
}

int main(void)
{ 
  FILE* fin = fopen("mergesort.in", "r");
  FILE* fout = fopen("mergesort.out", "w");
  if (fin == NULL || fout == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  int n;
  if (fscanf(fin, "%d", &n) != 1) {
    fprintf(stderr, "cannot read n\n");
    exit(EXIT_FAILURE);
  }
  
  int* A = (int*)malloc(n * sizeof(int));
  if (A == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < n; i++) {
    if (fscanf(fin, "%d", &A[i]) != 1) {
      fprintf(stderr, "cannot read data\n");
      exit(EXIT_FAILURE);
    }
  }

  mergesort(A, n);

  for(int i = 0; i < n; i++) {
    fprintf(fout, i == n - 1 ? "%d\n" : "%d ", A[i]);
  }

  free(A);
  fclose(fin);
  fclose(fout);

  return EXIT_SUCCESS;
}
