#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void insertsort(int* A, int n)
{
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--) {
      if (A[j - 1] <= A[j]) {
        break;
      }
        
      swap(&A[j - 1], &A[j]);
    }
  }
}

typedef struct {
  int mid_left;
  int mid_right;
} partition_rv_t;

partition_rv_t partition(int* A, int left, int right, int k)
{
  swap(&A[left], &A[k]);
  int mid_left = left;
  int mid_right = left + 1;

  for (int i = left + 1; i < right; i++) {
    if (A[i] > A[mid_left]) {
      continue;
    }

    if (A[i] < A[mid_left]) {
      swap(&A[mid_left], &A[i]);
      mid_left++;
    }

    swap(&A[mid_right], &A[i]);
    mid_right++;
  }

  partition_rv_t rv;
  rv.mid_left = mid_left;
  rv.mid_right = mid_right;
  return rv;
}

int linear_select(int* A, int left, int right, int k)
{
  int n = right - left;
  if (n <= 5) {
    insertsort(A + left, n);
    return k;
  }

  int m = (n - 1) / 5;
  int* M = malloc((m + 1) * sizeof(int));
  if (M == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < m; i++) {
    M[i] = A[linear_select(A, left + 5 * i, left + 5 * i + 5, left + 5 * i + 2)];
  }
  M[m] = A[linear_select(A, left + 5 * m, left + 5 * m + (n - 1) % 5 + 1, left + 5 * m + (((n - 1) % 5 + 1) / 2))];

  int pos = linear_select(M, 0, m + 1, (m + 1) / 2);

  free(M);

  pos = pos * 5 + 2;

  partition_rv_t rv = partition(A, left, right, pos);

  if (k < rv.mid_left) {
    return linear_select(A, left, rv.mid_left, k);
  } else if (k > rv.mid_right) {
    return linear_select(A, rv.mid_right, right, k);
  } else {
    return k;
  }
}

int main()
{
  FILE* fin = fopen("select.in", "right");
  FILE* fout = fopen("select.out", "w");
  if (fin == NULL || fout == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  int n;
  int k;
  if (fscanf(fin, "%d %d", &n, &k) != 2) {
    fprintf(stderr, "cannot read n or k\n");
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

  int i = linear_select(A, 0, n, k - 1);

  fprintf(fout, "%d\n", A[i]);

  free(A);
  fclose(fin);
  fclose(fout);

  return EXIT_SUCCESS;
}
