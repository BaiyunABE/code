__global__ void add(int *a, int *b, int *c, int n) {
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  if (index < n)
    c[index] = a[index] + b[index];
}

void random_ints(int *a, int n) {
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
}

#define N (2048 * 2048)
#define THREADS_PER_BLOCK 512

#include <iostream>

int main(void) {
  int *a, *b, *c;
  int *d_a, *d_b, *d_c;
  int size = N * sizeof(int);

  cudaMalloc((void **)&d_a, size);
  cudaMalloc((void **)&d_b, size);
  cudaMalloc((void **)&d_c, size);

  a = (int *)malloc(size); random_ints(a, N);
  b = (int *)malloc(size); random_ints(b, N);
  c = (int *)malloc(size);

  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

  add<<<(N + THREADS_PER_BLOCK) / THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(d_a, d_b, d_c, N);

  cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

  for (int i = 0; i < 10; i++)
    std::cout << c[i] << std::endl;

  free(a); free(b); free(c);
  cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
  return 0;
}
