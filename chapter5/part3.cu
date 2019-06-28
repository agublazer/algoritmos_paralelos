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
