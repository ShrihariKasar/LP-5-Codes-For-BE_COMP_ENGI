// Assignment 3: Implement Min, Max, Sum and Average Operations using Parallel Reduction with OpenMP

#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

int main() {

    vector<int> arr = {10, 20, 5, 40, 25, 15, 30};

    int n = arr.size();

    int minimum = INT_MAX;
    int maximum = INT_MIN;
    int sum = 0;

    double average;

    // Parallel Reduction for Sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Parallel Reduction for Minimum
    #pragma omp parallel for reduction(min:minimum)
    for (int i = 0; i < n; i++) {

        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }

    // Parallel Reduction for Maximum
    #pragma omp parallel for reduction(max:maximum)
    for (int i = 0; i < n; i++) {

        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }

    average = (double)sum / n;

    cout << "Array Elements: ";

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;

    cout << "Minimum Value: " << minimum << endl;
    cout << "Maximum Value: " << maximum << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}