#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000   // 1 million elements
#define INSERTION_THRESHOLD 10 // Switch to insertion sort for small arrays

// Insertion sort for small partitions
void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Median-of-three pivot selection
int medianOfThree(int arr[], int low, int high) {
    int mid = (low + high) / 2;

    if (arr[low] > arr[mid]) { int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t; }
    if (arr[low] > arr[high]) { int t = arr[low]; arr[low] = arr[high]; arr[high] = t; }
    if (arr[mid] > arr[high]) { int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t; }

    int t = arr[mid];
    arr[mid] = arr[high];
    arr[high] = t;

    return arr[high];
}

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// QuickSort with insertion sort optimization
void quickSort(int arr[], int low, int high) {
    while (low < high) {
        if (high - low < INSERTION_THRESHOLD) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pi = partition(arr, low, high);

            // Tail recursion optimization: sort smaller half first
            if (pi - low < high - pi) {
                quickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

int main() {
    int *arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    clock_t start = clock();
    quickSort(arr, 0, SIZE - 1);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Optimized QuickSort (median-of-three + insertion sort) of %d elements took %.2f seconds.\n", SIZE, time_taken);

    free(arr);
    return 0;
}
