#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cuda_runtime.h>

const int N = 1024;
const int BLOCK_SIZE = 16;

// CPU朴素矩阵乘法 C = A * B
void cpu_matmul(float *A, float *B, float *C)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            float sum = 0.0f;
            for(int k = 0; k < N; k++)
            {
                sum += A[i*N + k] * B[k*N + j];
            }
            C[i*N + j] = sum;
        }
    }
}

// GPU朴素kernel：一个线程计算C[i][j]
__global__ void gpu_basic_matmul(const float *A, const float *B, float *C)
{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < N && j < N)
    {
        float sum = 0.0f;
        for(int k = 0; k < N; k++)
        {
            sum += A[i*N + k] * B[k*N + j];
        }
        C[i*N + j] = sum;
    }
}

// GPU共享内存分块版本 tiling
__global__ void gpu_shared_matmul(const float *A, const float *B, float *C)
{
    __shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int i = blockIdx.y * BLOCK_SIZE + ty;
    int j = blockIdx.x * BLOCK_SIZE + tx;

    float sum = 0.0f;

    // 遍历所有块
    for(int t = 0; t < N / BLOCK_SIZE; t++)
    {
        // 将A、B对应块加载到共享内存
        As[ty][tx] = A[ i*N + t*BLOCK_SIZE + tx ];
        Bs[ty][tx] = B[ (t*BLOCK_SIZE + ty)*N + j ];

        __syncthreads();

        // 在共享内存内做小块乘法
        for(int k = 0; k < BLOCK_SIZE; k++)
        {
            sum += As[ty][k] * Bs[k][tx];
        }
        __syncthreads();
    }

    if(i < N && j < N)
    {
        C[i*N + j] = sum;
    }
}

int main(void)
{
    // host内存
    float *hA = (float*)malloc(N*N*sizeof(float));
    float *hB = (float*)malloc(N*N*sizeof(float));
    float *hC = (float*)malloc(N*N*sizeof(float));

    for(int i = 0; i < N*N; i++)
    {
        hA[i] = rand() / (float)RAND_MAX;
        hB[i] = rand() / (float)RAND_MAX;
    }

    // ===== CPU计时 =====
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        cpu_matmul(hA, hB, hC);
        auto t1 = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double,std::milli>(t1-t0).count();
        std::cout << "CPU matmul time: " << ms << " ms\n";
    }

    // ===== GPU准备device内存 =====
    float *dA, *dB, *dC;
    cudaMalloc(&dA, N*N*sizeof(float));
    cudaMalloc(&dB, N*N*sizeof(float));
    cudaMalloc(&dC, N*N*sizeof(float));

    cudaMemcpy(dA, hA, N*N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, N*N*sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
    dim3 grid(N/BLOCK_SIZE, N/BLOCK_SIZE);

    // ===== GPU朴素版本计时 =====
    {
        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        gpu_basic_matmul<<<grid, block>>>(dA, dB, dC);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        float ms;
        cudaEventElapsedTime(&ms, start, stop);
        std::cout << "GPU basic matmul time: " << ms << " ms\n";
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    // ===== GPU共享内存分块版本计时 =====
    {
        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        gpu_shared_matmul<<<grid, block>>>(dA, dB, dC);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        float ms;
        cudaEventElapsedTime(&ms, start, stop);
        std::cout << "GPU shared‑mem matmul time: " << ms << " ms\n";
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    // free
    cudaFree(dA); cudaFree(dB); cudaFree(dC);
    free(hA); free(hB); free(hC);
    return 0;
}
