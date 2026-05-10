// Assignment 5: Write a CUDA Program for Matrix Multiplication using CUDA C

#include <iostream>
#include <cuda_runtime.h>

using namespace std;

#define SIZE 3

// CUDA Kernel Function
__global__ void matrixMultiplication(int A[SIZE][SIZE],
                                     int B[SIZE][SIZE],
                                     int C[SIZE][SIZE]) {

    int row = threadIdx.y;
    int col = threadIdx.x;

    int sum = 0;

    for (int k = 0; k < SIZE; k++) {
        sum += A[row][k] * B[k][col];
    }

    C[row][col] = sum;
}

int main() {

    int h_A[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int h_B[SIZE][SIZE] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    int h_C[SIZE][SIZE];

    int (*d_A)[SIZE], (*d_B)[SIZE], (*d_C)[SIZE];

    int bytes = SIZE * SIZE * sizeof(int);

    // Allocate GPU Memory
    cudaMalloc((void**)&d_A, bytes);
    cudaMalloc((void**)&d_B, bytes);
    cudaMalloc((void**)&d_C, bytes);

    // Copy Data from Host to Device
    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    // Define CUDA Thread Configuration
    dim3 threadsPerBlock(SIZE, SIZE);

    // Launch Kernel
    matrixMultiplication<<<1, threadsPerBlock>>>(d_A, d_B, d_C);

    // Copy Result back to Host
    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    cout << "Matrix A:" << endl;

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            cout << h_A[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    cout << "Matrix B:" << endl;

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            cout << h_B[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    cout << "Matrix Multiplication Result:" << endl;

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            cout << h_C[i][j] << " ";
        }

        cout << endl;
    }

    // Free GPU Memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}