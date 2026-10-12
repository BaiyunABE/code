#define BLOCK_SIZE 9
#define RADIUS 3

__global__ void stencil_1d(int *in, int *out) {
  __shared__ int temp[BLOCK_SIZE + 2 * RADIUS];
  int gindex = threadIdx.x + blockIdx.x * blockDim.x;
  int lindex = threadIdx.x + RADIUS;

  temp[lindex] = in[gindex];
  if (threadIdx.x < RADIUS) {
    temp[lindex - RADIUS] = in[gindex - RADIUS];
    temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE];
  }

  __syncthreads();

  int result = 0;
  for (int offset = -RADIUS; offset <= RADIUS; offset++)
    result += temp[lindex + offset];

  out[gindex] = result;
}

#include <iostream>

int main(void) {
  int *in, *out;
  int *d_in, *d_out;

  in = (int *)malloc((BLOCK_SIZE + 2 * RADIUS) * sizeof(int));
  out = (int *)malloc(BLOCK_SIZE * sizeof(int));

  cudaMalloc((void **)&d_in, (BLOCK_SIZE + 2 * RADIUS) * sizeof(int));
  cudaMalloc((void **)&d_out,  BLOCK_SIZE * sizeof(int));

  for (int i = 0; i < BLOCK_SIZE + 2 * RADIUS; i++)
    in[i] = 1;

  cudaMemcpy(d_in, in, (BLOCK_SIZE + 2 * RADIUS) * sizeof(int), cudaMemcpyHostToDevice);

  stencil_1d<<<1, BLOCK_SIZE>>>(d_in + RADIUS, d_out);

  cudaMemcpy(out, d_out, BLOCK_SIZE * sizeof(int), cudaMemcpyDeviceToHost);

  for (int i = 0; i < BLOCK_SIZE; i++)
    std::cout << out[i] << std::endl;

  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out);

  return 0;
}
