#include <stdio.h>
#include <stdlib.h>

int quicksort_calls = 0; // Global counter for quicksort calls

// Function to swap two elements
void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(double arr[], int low, int high) {
    double pivot = arr[high]; // Pivot is the last element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]); // Swap elements smaller than pivot
        }
    }
    swap(&arr[i + 1], &arr[high]); // Move pivot to correct position
    return i + 1; // Return the index of the pivot
}

// Quicksort function
void quicksort(double arr[], int low, int high, char pivot_choice) {
    if (low < high) {
        quicksort_calls++; // Increment quicksort call counter
        
        int pivot_index = high; // Default pivot is the last element

        // Modify pivot selection based on pivot_choice
        if (pivot_choice == 'm') { // Middle element as pivot
            pivot_index = (low + high) / 2; // Calculate the middle index
            swap(&arr[pivot_index], &arr[high]); // Swap middle element with the last
        } else if (pivot_choice == 'r' && low != high) { // Random element as pivot
            // Ensure rand() is not called when subarray size is 1
            pivot_index = low + rand() % (high - low + 1); // Random index within range
            swap(&arr[pivot_index], &arr[high]); // Swap random element with the last
        }

        // Partition the array
        int pi = partition(arr, low, high); // pi is the partitioning index

        // Recursively sort the subarrays
        quicksort(arr, low, pi - 1, pivot_choice); // Sort the left subarray
        quicksort(arr, pi + 1, high, pivot_choice); // Sort the right subarray
    }
}

// Function to read the input file and populate the array
void read_file(const char *filename, double **arr, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", size); // Read the number of elements
    *arr = (double *)malloc(*size * sizeof(double));

    for (int i = 0; i < *size; i++) {
        fscanf(file, "%lf", &((*arr)[i]));
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <pivot_choice>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Command line arguments
    char *filename = argv[1];
    char pivot_choice = argv[2][0];

    if (pivot_choice != 'l' && pivot_choice != 'm' && pivot_choice != 'r') {
        printf("Invalid pivot choice. Use 'l' for last, 'm' for middle, or 'r' for random.\n");
        return EXIT_FAILURE;
    }

    // Read data from the file
    double *arr;
    int size;
    read_file(filename, &arr, &size);

    // Seed the random number generator for random pivot choice
    srand(0);

    // Perform quicksort
    quicksort(arr, 0, size - 1, pivot_choice);

    // Output the number of quicksort calls, multiply by 2, and add 1
    printf("%d\n", (quicksort_calls * 2) + 1);

    // Free dynamically allocated memory
    free(arr);

    return EXIT_SUCCESS;
}
