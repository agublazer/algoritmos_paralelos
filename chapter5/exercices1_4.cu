// Kernel de 5.13 modificado (Ejercicio 5.1)
__global__
void kernel513modified(float* X, float *Y, int size) {
  extern __shared__ float partialSum[];
	unsigned int t = threadIdx.x;
	partialSum[t] = 0;
	if (blockIdx.x*blockDim.x + threadIdx.x < size) {
		partialSum[t] = X[blockIdx.x*blockDim.x + threadIdx.x];
	}
	__syncthreads();
	for (unsigned int stride = 1; stride < 2048; stride <<= 2) {
		if (t % (2 * stride) == 0) {
			partialSum[t] += partialSum[t + stride];
		}
		__syncthreads();  // previene a los threads de sobreescribir la memoria compartida si terminan antes
	}
}

// Kernel de 5.15 modificado (Ejercicio 5.1)
__global__
void kernel515modified(float* X, float* Y, int size) {
	extern __shared__ float partialSum[];
	unsigned int t = threadIdx.x;
	partialSum[t] = 0;
	if (blockIdx.x*blockDim.x + threadIdx.x < size) {
		partialSum[t] = X[blockIdx.x*blockDim.x + threadIdx.x];
	}
	__syncthreads();
	for (unsigned int stride = blockDim.x/2; stride > 0; stride >>= 1) {
		if (t < stride) {
			partialSum[t] += partialSum[t + stride];
		}
		__syncthreads();
	}
}

// Kernel basado en 5.1 (Ejercicio 3)
__global__
void 51basedkernel(float* X, float* Y, int size) {
	extern __shared__ float partialSum[];
	unsigned int t = threadIdx.x;
	unsigned int i = ;
	partialSum[t] = 0;
	if (blockIdx.x*(blockDim.x*2) + threadIdx.x < size) {
		partialSum[t] = X[blockIdx.x*(blockDim.x*2) + threadIdx.x];
    partialSum[t] += X[blockIdx.x*(blockDim.x*2) + threadIdx.x + blockDim.x];
	}
	__syncthreads();
	for (unsigned int stride = blockDim.x/2; stride > 0; stride >>= 1) {
		if (t < stride) {
			partialSum[t] += partialSum[t + stride];
		}
		__syncthreads();
	}
}

