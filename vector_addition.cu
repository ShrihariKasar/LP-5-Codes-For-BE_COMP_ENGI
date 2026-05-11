// Assignment 4: Write a CUDA Program for Addition of Two Large Vectors

#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// CUDA Kernel Function
__global__ void vectorAddition(int *A, int *B, int *C, int n) {

    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < n) {
        C[index] = A[index] + B[index];
    }
}

int main() {

    int n = 10;
    int size = n * sizeof(int);

    int h_A[n], h_B[n], h_C[n];

    // Initialize Host Vectors
    for (int i = 0; i < n; i++) {

        h_A[i] = i + 1;
        h_B[i] = (i + 1) * 2;
    }

    int *d_A, *d_B, *d_C;

    // Allocate Memory on GPU
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Copy Data from Host to Device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Define CUDA Configuration
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    // Launch Kernel
    vectorAddition<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, n);

    // Copy Result back to Host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    cout << "Vector A: ";
    for (int i = 0; i < n; i++) {
        cout << h_A[i] << " ";
    }

    cout << endl;

    cout << "Vector B: ";
    for (int i = 0; i < n; i++) {
        cout << h_B[i] << " ";
    }

    cout << endl;

    cout << "Vector Addition Result: ";
    for (int i = 0; i < n; i++) {
        cout << h_C[i] << " ";
    }

    cout << endl;

    // Free GPU Memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
