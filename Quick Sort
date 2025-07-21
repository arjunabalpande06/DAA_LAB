#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function used in Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot element
    int i = (low - 1); // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is less than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // increment index
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]); // place pivot at the correct position
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int n;

    // Take input for size of array
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    // Take input for array elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Perform Quick Sort
    quickSort(arr, 0, n - 1);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
