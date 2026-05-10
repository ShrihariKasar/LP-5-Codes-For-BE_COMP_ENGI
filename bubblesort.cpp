// Assignment 2(a): Write a Program to Implement Parallel Bubble Sort using OpenMP
// Measure Performance of Sequential and Parallel Bubble Sort

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Odd Phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Even Phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Display Array
void display(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;
}

int main() {

    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    vector<int> arr2 = arr1;

    double start, end;

    // Sequential Bubble Sort
    start = omp_get_wtime();

    sequentialBubbleSort(arr1);

    end = omp_get_wtime();

    cout << "Sequential Bubble Sort: ";
    display(arr1);

    cout << "Sequential Execution Time: "
         << end - start << " seconds" << endl;


    // Parallel Bubble Sort
    start = omp_get_wtime();

    parallelBubbleSort(arr2);

    end = omp_get_wtime();

    cout << "Parallel Bubble Sort: ";
    display(arr2);

    cout << "Parallel Execution Time: "
         << end - start << " seconds" << endl;

    return 0;
}