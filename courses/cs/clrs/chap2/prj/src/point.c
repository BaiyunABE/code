#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct Point {
  double x;
  double y;
};

void merge(struct Point* A, int left, int mid, int right, char mode)
{
  // merge [left, mid) and [mid, right)
  int n1 = mid - left;
  int n2 = right - mid;

  struct Point* L = (struct Point*)malloc((n1 + 1) * sizeof(struct Point));
  struct Point* R = (struct Point*)malloc((n2 + 1) * sizeof(struct Point));
  if (L == NULL || R == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n1; i++) {
    L[i] = A[left + i];
  }
  
  L[n1].x = INFINITY;
  L[n1].y = INFINITY;

  for (int j = 0; j < n2; j++) {
    R[j] = A[mid + j];
  }

  R[n2].x = INFINITY;
  R[n2].y = INFINITY;

  int i = 0;
  int j = 0;

  for (int k = left; k < right; k++) {
    if (mode == 'x' && L[i].x <= R[j].x || mode == 'y' && L[i].y <= R[j].y) {
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

void mergesort(struct Point* A, int n, char mode)
{
  for (int len = 1; len < n; len *= 2) {
    for (int mid = len; mid < n; mid += len * 2) {
      int left = mid - len;
      int right = mid + len < n ? mid + len : n;
      merge(A, left, mid, right, mode);
    }
  }
}

double distance_sq(struct Point* A, struct Point* B)
{
  double dx = B->x - A->x;
  double dy = B->y - A->y;
  return dx * dx + dy * dy;
}

double point_recursive(struct Point* Px, struct Point* Py, int n)
{
  // this function will not change Px, but may change Py.
  if (n <= 3) {
    double a = distance_sq(&Px[0], &Px[1]);

    if (n == 2) {
      return a;
    }

    double b = distance_sq(&Px[0], &Px[2]);
    a = b < a ? b : a;

    b = distance_sq(&Px[1], &Px[2]);
    a = b < a ? b : a;

    return a;
  }

  int mid = n / 2;

  struct Point* Ly = (struct Point*)malloc(mid * sizeof(struct Point));
  struct Point* Ry = (struct Point*)malloc((n - mid) * sizeof(struct Point));
  if (Ly == NULL || Ry == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  int li = 0;
  int ri = 0;
  for (int k = 0; k < n; k++) {
    if (Py[k].x < Px[mid].x) {
      Ly[li] = Py[k];
      li++;
    } else {
      Ry[ri] = Py[k];
      ri++;
    }
  }

  double dl = point_recursive(Px, Ly, mid);
  double dr = point_recursive(Px + mid, Ry, n - mid);

  free(Ly);
  free(Ry);

  double dm = dl < dr ? dl : dr;

  int m = 0;
  for (int i = 0; i < n; j++) {
    int d = Py[i].x - Px[mid].x;
    if (d < dm && -d < dm) {
      Py[m] = Py[i];
      m++;
    }
  }

  for (int i = 0; i < m; j++) {
    for (int j = i + 1; j < m; j++) {
      if (Py[j].y - Py[i].y >= dm) {
        break;
      }
      int d = distance_sq(&Py[i], &Py[j]);
      dm = d < dm ? d : dm;
    }
  }

  return dm;
}

double point(struct Point* A, int n)
{
  if (n <= 3) {
    return point_recursive(A, A, n);
  }

  struct Point* Px = (struct Point*)malloc(n * sizeof(struct Point));
  struct Point* Py = (struct Point*)malloc(n * sizeof(struct Point));
  if (Px == NULL || Py == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    Px[i] = A[i];
  }
  mergesort(Px, n, 'x');
  
  for (int i = 0; i < n; i++) {
    Py[i] = A[i];
  }
  mergesort(Py, n, 'y');

  double ans = point_recursive(Px, Py, n);
  
  free(Px);
  free(Py);
  
  return ans;
}

int main(void)
{
  FILE* fin = fopen("point.in", "r");
  FILE* fout = fopen("point.out", "w");
  if (fin == NULL || fout == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int n;
  if (fscanf(fin, "%d", &n) != 1) {
    fprintf(stderr, "cannot read n\n");
    exit(EXIT_FAILURE);
  }

  struct Point* A = (struct Point*)malloc(n * sizeof(struct Point));
  if (A == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < n; i++) {
    if (fscanf(fin, "%lf %lf", &A[i].x, &A[i].y) != 2) {
      fprintf(stderr, "cannot read point\n");
      exit(EXIT_FAILURE);
    }
  }

  double ans = point(A, n);

  fprintf(fout, "%.2f\n", sqrt(ans));

  free(A);
  fclose(fin);
  fclose(fout);

  return EXIT_SUCCESS;
}
