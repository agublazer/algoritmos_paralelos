#include <cuda.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <chrono>
using namespace std;
int channels = 3;

__global__
void colorToGreyscaleConversion(int * Pout, int * Pin, int width, int height) {
    int Col = threadIdx.x + blockIdx.x * blockDim.x;
    int Row = threadIdx.y + blockIdx.y * blockDim.y;
    if (Col < width && Row < height) {
        // get 1D coordinate for the grayscale image
        int greyOffset = Row*width + Col;
        // one can think of the RGB image having
        // CHANNEL times columns than the grayscale image
        int rgbOffset = greyOffset*channels;
        int r = Pin[rgbOffset ]; // red value for pixel
        int g = Pin[rgbOffset + 1]; // green value for pixel
        int b = Pin[rgbOffset + 2]; // blue value for pixel
        float pixel_avg = 0.0;
        pixel_avg = (r + g + b)/3;

        Pout[grayOffset] = (int)pixel_avg;
        Pout[grayOffset + 1] = (int)pixel_avg;
        Pout[grayOffset + 2] = (int)pixel_avg;
    }
}

void colorToGreyscale(int* A, int* B, int width, int height) {
        int size = height*width*3 * sizeof(int);
        int *d_A, *d_B;
        cudaMalloc(&d_A, size);
        cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

        cudaMalloc(&d_B, size);

        // colorToGreyscale<<< ceil(n/256.0), 256 >>> (d_A, d_B, width, height);
        dim3 dimGrid(ceil(width/16.0), ceil(height/16.0), 1);
        dim3 dimBlock(16, 16, 1);
        colorToGreyscaleConversion<<<dimGrid,dimBlock>>>(d_A, d_B, width, height);
        
	    cudaMemcpy(B, d_B, size, cudaMemcpyDeviceToHost);


        cudaFree(d_A);
        cudaFree(d_B);
}

int main() {
        FILE *myFile;
        myFile = fopen("pixels1.txt", "r");

        //read file into array
        int w = 301;
        int h = 168;
        int pixel_array[w*h];

        for (int i = 0; i < w*h; i++)
        {
            fscanf(myFile, "%d", &pixel_array[i]);
        }

        int *pixel_gray;
        pixel_gray = (float*)malloc(w*h * sizeof(int));

    	colorToGreyscale(pixel_array, pixel_gray, w, h);

        
        free(h_A);
        free(h_B);
        free(h_C);

        return 0;
}