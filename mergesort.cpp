// Assignment 2(b): Write a Program to Implement Parallel Merge Sort using OpenMP
// Measure Performance of Sequential and Parallel Merge Sort

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge Function
void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
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

    vector<int> arr1 = {38, 27, 43, 3, 9, 82, 10};
    vector<int> arr2 = arr1;

    double start, end;

    // Sequential Merge Sort
    start = omp_get_wtime();

    sequentialMergeSort(arr1, 0, arr1.size() - 1);

    end = omp_get_wtime();

    cout << "Sequential Merge Sort: ";
    display(arr1);

    cout << "Sequential Execution Time: "
         << end - start << " seconds" << endl;


    // Parallel Merge Sort
    start = omp_get_wtime();

    parallelMergeSort(arr2, 0, arr2.size() - 1);

    end = omp_get_wtime();

    cout << "Parallel Merge Sort: ";
    display(arr2);

    cout << "Parallel Execution Time: "
         << end - start << " seconds" << endl;

    return 0;
}