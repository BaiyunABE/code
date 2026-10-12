#include <stdio.h>
#include <stdlib.h>

int partition(int* A, int left, int right)
{
  int pivot = A[left];
  int i = left;
  int j = right - 1;

  while (i != j) {
    while (i != j && A[j] >= pivot) {
      j--;
    }

    A[i] = A[j];

    while (i != j && A[i] <= pivot) {
      i++;
    }

    A[j] = A[i];
  }

  A[i] = pivot;

  return i;
}

void quicksort(int* A, int left, int right)
{
  if (left + 1 >= right) {
    return;
  }

  int pivot = partition(A, left, right);
  quicksort(A, left, pivot);
  quicksort(A, pivot + 1, right);
}

int main()
{
  FILE* fin = fopen("quicksort.in", "r");
  FILE* fout = fopen("quicksort.out", "w");
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

  quicksort(A, 0, n);

  for(int i = 0; i < n; i++) {
    fprintf(fout, i == n - 1 ? "%d\n" : "%d ", A[i]);
  }

  free(A);
  fclose(fin);
  fclose(fout);

  return EXIT_SUCCESS;
}
