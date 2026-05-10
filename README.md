# C++ OpenMP Setup Guide

This guide explains how to install and configure the C++ compiler required for OpenMP programs on Windows.

---

# Required Installations

## 1. Install MinGW-w64 (for g++ compiler)

Use the ZIP file already available in the project folder.

If the files get corrupted, download again from:

[WinLibs Official Website](https://winlibs.com/?utm_source=chatgpt.com)
# https://winlibs.com/ on this page
Release versions
UCRT runtime
GCC 16.1.0 (with POSIX threads) + MinGW-w64 14.0.0 (UCRT) - release 1   (LATEST)
# Download --> Zip archive
# Win64 (without LLVM/Clang/LLD/LLDB): 7-Zip archive* | Zip archive
Download Version:

- UCRT Runtime
- POSIX threads
- SEH (for 64-bit Windows)

Example File:

```text
winlibs-x86_64-posix-seh-gcc-14.x.x.zip
```

---

# 2. Extract Files

Extract the ZIP file to:

```text
C:\mingw64
```

You should get:

```text
C:\mingw64\bin
```

Inside the folder:

```text
g++.exe
gcc.exe
```

---

# 3. Add Compiler to PATH

## Open

```text
Windows Search → Environment Variables
```

Open:

```text
Edit the system environment variables
```

Then click:

```text
Environment Variables
```

Under:

```text
System Variables
```

Select:

```text
Path
```

Click:

```text
Edit → New
```

Add:

```text
C:\mingw64\bin
```

Click OK everywhere.

---

# 4. Restart PowerShell / VS Code

Close and reopen PowerShell or VS Code.

Then verify installation:

```powershell
g++ --version
```

If installed correctly:

```text
g++ (GCC) 14.x.x
```

---

# 5. Compile OpenMP Programs

Example:

```powershell
g++ bfs.cpp -fopenmp -o bfs
./bfs
```

---

# Notes

- OpenMP support is enabled using:

```text
-fopenmp
```

- `g++` is the GNU C++ compiler.
- OpenMP allows parallel execution using multiple CPU threads.
- Use PowerShell, CMD, or VS Code terminal for compilation.
  
# Parallel Computing and CUDA Programs

This repository contains implementations of Parallel Computing algorithms using OpenMP and CUDA C.  
The programs demonstrate graph traversal, sorting algorithms, reduction operations, vector addition, and matrix multiplication using parallel programming techniques.

---

# Technologies Used

- C++
- OpenMP
- CUDA C
- NVIDIA CUDA Toolkit
- g++

---

# Assignment 1(a): Design and Implement Parallel Breadth First Search (BFS) using OpenMP

## Compilation Command

```bash
g++ bfs.cpp -fopenmp -o bfs
```

## Run

```bash
./bfs
```

## Sample Output

```text
Parallel BFS Traversal: 0 1 2 3 4 5 6
```

## Viva Points

- BFS explores graph level by level.
- OpenMP is used for parallel neighbor traversal.
- `#pragma omp parallel for` distributes work among threads.
- `#pragma omp critical` avoids race conditions while accessing shared queue and visited array.
- Graph used is undirected.

---

# Assignment 1(b): Design and Implement Parallel Depth First Search (DFS) using OpenMP

## Compilation Command

```bash
g++ dfs.cpp -fopenmp -o dfs
```

## Run

```bash
./dfs
```

## Sample Output

```text
Parallel DFS Traversal: 0 2 6 5 1 4 3
```

## Viva Points

- DFS explores graph depth-wise.
- Stack data structure is used instead of recursion.
- OpenMP parallelizes adjacent node traversal.
- `#pragma omp critical` prevents race conditions on shared stack.
- Traversal order may vary due to parallel execution.

---

# Assignment 2(a): Write a Program to Implement Parallel Bubble Sort using OpenMP

## Compilation Command

```bash
g++ bubblesort.cpp -fopenmp -o bubblesort
```

## Run

```bash
./bubblesort
```

## Sample Output

```text
Sequential Bubble Sort: 11 12 22 25 34 64 90
Sequential Execution Time: 0.000001 seconds

Parallel Bubble Sort: 11 12 22 25 34 64 90
Parallel Execution Time: 0.000120 seconds
```

## Viva Points

- Bubble Sort repeatedly swaps adjacent elements.
- Parallel Bubble Sort uses Odd-Even Transposition method.
- OpenMP parallelizes odd and even phases separately.
- `omp_get_wtime()` measures execution time.
- Parallel version is beneficial for large datasets.

---

# Assignment 2(b): Write a Program to Implement Parallel Merge Sort using OpenMP

## Compilation Command

```bash
g++ mergesort.cpp -fopenmp -o mergesort
```

## Run

```bash
./mergesort
```

## Sample Output

```text
Sequential Merge Sort: 3 9 10 27 38 43 82
Sequential Execution Time: 0.000002 seconds

Parallel Merge Sort: 3 9 10 27 38 43 82
Parallel Execution Time: 0.000145 seconds
```

## Viva Points

- Merge Sort follows Divide and Conquer approach.
- Array is recursively divided into smaller subarrays.
- OpenMP parallel sections executes recursive halves simultaneously.
- Merge function combines sorted subarrays.
- Parallel Merge Sort improves performance on large datasets.

---

# Assignment 3: Implement Min, Max, Sum and Average Operations using Parallel Reduction with OpenMP

## Compilation Command

```bash
g++ reduction.cpp -fopenmp -o reduction
```

## Run

```bash
./reduction
```

## Sample Output

```text
Array Elements: 10 20 5 40 25 15 30

Minimum Value: 5
Maximum Value: 40
Sum: 145
Average: 20.7143
```

## Viva Points

- Reduction combines values from multiple threads safely.
- OpenMP reduction clause avoids race conditions.
- `reduction(+:sum)` performs parallel summation.
- `reduction(min:minimum)` finds minimum value.
- `reduction(max:maximum)` finds maximum value.
- Average is calculated using total sum divided by number of elements.

---

# Assignment 4: Write a CUDA Program for Addition of Two Large Vectors

## Compilation Command

```bash
nvcc vector_addition.cu -o vector_addition
```

## Run

```bash
./vector_addition
```

## Sample Output

```text
Vector A: 1 2 3 4 5 6 7 8 9 10
Vector B: 2 4 6 8 10 12 14 16 18 20
Vector Addition Result: 3 6 9 12 15 18 21 24 27 30
```

## Viva Points

- CUDA is NVIDIA’s parallel computing platform.
- GPU executes thousands of threads simultaneously.
- `__global__` defines GPU kernel function.
- `threadIdx`, `blockIdx`, and `blockDim` calculate unique thread index.
- `cudaMalloc()` allocates GPU memory.
- `cudaMemcpy()` transfers data between CPU and GPU.

### Kernel Launch Syntax

```cpp
kernel<<<blocks, threads>>>();
```

---

# Assignment 5: Write a CUDA Program for Matrix Multiplication using CUDA C

## Compilation Command

```bash
nvcc matrix_multiplication.cu -o matrix_multiplication
```

## Run

```bash
./matrix_multiplication
```

## Sample Output

```text
Matrix A:
1 2 3
4 5 6
7 8 9

Matrix B:
1 0 0
0 1 0
0 0 1

Matrix Multiplication Result:
1 2 3
4 5 6
7 8 9
```

## Viva Points

- Matrix multiplication is parallelized using CUDA threads.
- Each thread computes one matrix element.
- `threadIdx.x` represents column index.
- `threadIdx.y` represents row index.
- GPU executes matrix computations in parallel.
- `dim3` defines 2D thread block configuration.
- CUDA significantly improves computation speed for large matrices.

---

# Conclusion

These programs demonstrate the implementation of parallel computing concepts using OpenMP and CUDA C.  
The assignments cover graph traversal algorithms, sorting algorithms, reduction operations, vector addition, and matrix multiplication using CPU and GPU parallelization techniques.

# Python Deep Learning Assignments

This repository contains Deep Learning programs implemented using Python and TensorFlow/Keras.  
The assignments demonstrate regression, binary classification, multiclass classification, and image classification using Deep Neural Networks.

---

# Technologies Used

- Python
- TensorFlow
- Keras
- NumPy
- Pandas
- Scikit-learn

---

# Assignment 9: Linear Regression using Deep Neural Network
# Boston Housing Price Prediction

## Install Required Libraries

```bash
pip install tensorflow scikit-learn pandas numpy
```

## Run

```bash
python boston_dnn.py
```

## Sample Output

```text
Mean Squared Error: 18.45

Actual Price vs Predicted Price

Actual: 7.20   Predicted: 8.11
Actual: 18.80  Predicted: 19.42
Actual: 19.00  Predicted: 20.15
```

## Viva Points

- Boston Housing dataset is used for regression problems.
- Deep Neural Network predicts house prices.
- Input features are normalized using StandardScaler.
- ReLU activation is used in hidden layers.
- Output layer has 1 neuron for continuous value prediction.
- Mean Squared Error (MSE) measures prediction accuracy.
- Adam optimizer improves training efficiency.

---

# Assignment 10: Binary Classification using Deep Neural Networks
# IMDB Movie Review Sentiment Classification

## Install Required Libraries

```bash
pip install tensorflow
```

## Run

```bash
python imdb_classification.py
```

## Sample Output

```text
Test Accuracy: 0.87

Prediction Value: 0.94
Predicted Sentiment: Positive Review
```

## Viva Points

- IMDB dataset contains movie reviews.
- Binary classification predicts positive or negative sentiment.
- Embedding layer converts words into dense vectors.
- Sigmoid activation is used for binary output.
- Binary Crossentropy is used as loss function.
- Accuracy measures classification performance.
- Deep Neural Networks learn patterns from text data.

---

# Assignment 11: Multiclass Classification using Deep Neural Networks
# OCR Letter Recognition using Deep Neural Network

## Install Required Libraries

```bash
pip install tensorflow pandas numpy scikit-learn
```

## Dataset Requirement

Copy the dataset file in the same folder:

```text
letter-recognition.csv
```

## Run

```bash
python ocr_classification.py
```

## Sample Output

```text
Test Accuracy: 0.97

Predicted Letter: A
Actual Letter: A
```

## Viva Points

- OCR dataset contains alphabet recognition data.
- Multiclass classification predicts 26 English letters.
- One-hot encoding is used for multiclass output.
- Softmax activation is used in output layer.
- Categorical Crossentropy handles multiclass loss.
- StandardScaler normalizes input features.
- Deep Neural Networks learn complex feature patterns.

---

# Assignment 12: Use MNIST Fashion Dataset and Create a Classifier
# Fashion Clothing Classification using Deep Neural Network

## Install Required Libraries

```bash
pip install tensorflow numpy
```

## Run

```bash
python fashion_mnist_classifier.py
```

## Sample Output

```text
Test Accuracy: 0.89

Predicted Category: Ankle Boot
Actual Category: Ankle Boot
```

## Viva Points

- Fashion MNIST dataset contains clothing images.
- Images are grayscale of size 28x28.
- Pixel normalization improves model performance.
- Flatten layer converts image into vector form.
- ReLU activation is used in hidden layers.
- Softmax activation performs multiclass classification.
- Sparse categorical crossentropy is used for multiclass loss.
- Dropout helps reduce overfitting.
- Deep Neural Networks learn image features automatically.

---

# Conclusion

These assignments demonstrate practical implementations of Deep Learning using TensorFlow and Keras.  
The programs cover regression, sentiment analysis, OCR letter recognition, and image classification using Deep Neural Networks.
