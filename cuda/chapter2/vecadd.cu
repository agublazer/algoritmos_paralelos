#include <cuda.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <chrono>

using namespace std;
// check for errors using cuda runtime api
// https://stackoverflow.com/questions/14038589/what-is-the-canonical-way-to-check-for-errors-using-the-cuda-runtime-api

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

void vecAdd1(float *h_A, float* h_B, float* h_C, int n) {
        for (int i = 0; i < n; i++) {
                h_C[i] = h_A[i] + h_B[i];
        }
}

__global__
void vecAddKernel(float* A, float* B, float* C, int n) {
        int i = blockDim.x*blockIdx.x + threadIdx.x;
        if (i < n) {
                C[i] = A[i] + B[i];
        }
}

void vecAdd2(float* A, float* B, float* C, int n) {
        int size = n * sizeof(float);
        float *d_A, *d_B, *d_C;
        cudaMalloc(&d_A, size);
        cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
        cudaMalloc(&d_B, size);
        cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

        cudaMalloc(&d_C, size);

        vecAddKernel <<< ceil(n/256.0), 256 >>> (d_A, d_B, d_C, n);
        
        cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

        cudaFree(d_A);
        cudaFree(d_B);
        cudaFree(d_C);
}

int main() {
        float *h_A, *h_B, *h_C;
        int n = 10;
        h_A = (float*)malloc(n * sizeof(float));
        h_B = (float*)malloc(n * sizeof(float));
        h_C = (float*)malloc(n * sizeof(float));
        for (int i = 0; i < n; i++) {
                h_A[i] = 10.0;
                h_B[i] = 20.0;
                h_C[i] = 0.0;
        }

	vecAdd2(h_A, h_B, h_C, n);

        for(int i = 0; i<n; i++){
        	printf("%f ", h_C[i]);
        }
	printf("\n");

        free(h_A);
        free(h_B);
        free(h_C);

        return 0;
}
