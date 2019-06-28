//Ejercicio 10
__global__
void figure517kernel(float* A, float* B, float* C, int Width) {
	__shared__ float Mds[TILE_WIDTH][WIDTH];
	__shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

	int bx = blockIdx.x;  int by = blockIdx.y;
	int tx = threadIdx.x; int ty = threadIdx.y;

	int Row = by * TILE_WIDTH + ty;
	int Col = bx * TILE_WIDTH + tx;

	float Pvalue = 0;
	for (int ph = 0; ph < ceil(Width / (float)TILE_WIDTH); ++ph) {
		if ((Row < Width) && ((ph*WIDTH + tx) < Width))
			Mds[ty][tx] = A[Row*Width + ph*WIDTH + tx];
		if (((ph*TILE_WIDTH + ty) < Width) && (Col < Width))
			Nds[ty][tx] = B[(ph*TILE_WIDTH + ty)*Width + Col];
		
    		__syncthreads(); //Nos aseguramos que todos los threads cargan los datos antes de continuar

		for (int k = 0; k < TILE_WIDTH; ++k) {
			Pvalue += Mds[ty][k] * Nds[k][tx];
		}
		__syncthreads(); // Nos aseguramos que todos los threads hayan usado los datos antes de jalar nuevos datos
	}
	if ((Row < Width) && (Col < Width))
		C[Row*Width + Col] = Pvalue;
}
