#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store each parking record
typedef struct {
    int entry_hour, entry_minute;     // Entry time in hours and minutes
    int exit_hour, exit_minute;       // Exit time in hours and minutes
    int lot_index;                    // Index of the parking lot
    int permit_number;                // Unique permit number for each car
    int duration;                     // Parking duration in minutes, calculated later
} ParkingRecord;

// Function to calculate the duration of parking in minutes
// Uses entry and exit times to compute total minutes parked
void calculate_duration(ParkingRecord *record) {
    record->duration = (record->exit_hour * 60 + record->exit_minute) - 
                       (record->entry_hour * 60 + record->entry_minute);
}

// Merge function to combine two sorted subarrays into one sorted array
// Handles both integer arrays (for durations) and ParkingRecord arrays
void merge(void *array, int left, int mid, int right, int key, int isDuration) {
    int n1 = mid - left + 1;   // Size of left subarray
    int n2 = right - mid;      // Size of right subarray

    if (isDuration) {  // If sorting integer durations
        int *L = (int *)malloc(n1 * sizeof(int));
        int *R = (int *)malloc(n2 * sizeof(int));

        // Copy data to temporary arrays L and R
        for (int i = 0; i < n1; i++)
            L[i] = ((int *)array)[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = ((int *)array)[mid + 1 + j];

        int i = 0, j = 0, k = left;

        // Merge the arrays into sorted order
        while (i < n1 && j < n2) {
            if (L[i] <= R[j])
                ((int *)array)[k++] = L[i++];
            else
                ((int *)array)[k++] = R[j++];
        }

        // Copy any remaining elements
        while (i < n1)
            ((int *)array)[k++] = L[i++];
        while (j < n2)
            ((int *)array)[k++] = R[j++];

        // Free the temporary arrays
        free(L);
        free(R);
    } else {  // If sorting ParkingRecords
        ParkingRecord *L = (ParkingRecord *)malloc(n1 * sizeof(ParkingRecord));
        ParkingRecord *R = (ParkingRecord *)malloc(n2 * sizeof(ParkingRecord));

        // Copy data to temporary arrays L and R
        for (int i = 0; i < n1; i++)
            L[i] = ((ParkingRecord *)array)[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = ((ParkingRecord *)array)[mid + 1 + j];

        int i = 0, j = 0, k = left;

        // Merge arrays based on the chosen sorting key
        while (i < n1 && j < n2) {
            if (key == 1) { // Sort by permit number
                if (L[i].permit_number <= R[j].permit_number)
                    ((ParkingRecord *)array)[k++] = L[i++];
                else
                    ((ParkingRecord *)array)[k++] = R[j++];
            } else if (key == 3) { // Sort by entry time
                int time1 = L[i].entry_hour * 60 + L[i].entry_minute;
                int time2 = R[j].entry_hour * 60 + R[j].entry_minute;
                if (time1 <= time2)
                    ((ParkingRecord *)array)[k++] = L[i++];
                else
                    ((ParkingRecord *)array)[k++] = R[j++];
            }
        }

        // Copy any remaining elements
        while (i < n1)
            ((ParkingRecord *)array)[k++] = L[i++];
        while (j < n2)
            ((ParkingRecord *)array)[k++] = R[j++];

        // Free the temporary arrays
        free(L);
        free(R);
    }
}

// Recursive merge sort function that can handle both integer and ParkingRecord arrays
void mergeSort(void *array, int left, int right, int key, int isDuration) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid, key, isDuration);
        mergeSort(array, mid + 1, right, key, isDuration);
        merge(array, left, mid, right, key, isDuration);
    }
}

// Process and print records with duplicate permit numbers
void process_duplicates(ParkingRecord *records, int num_records) {
    mergeSort(records, 0, num_records - 1, 1, 0); // Sort records by permit number

    int *printed = (int *)calloc(num_records, sizeof(int)); // Track printed records

    for (int i = 0; i < num_records - 1; i++) {
        // Check for duplicate permit numbers and print only once
        if (records[i].permit_number == records[i + 1].permit_number && !printed[i]) {
            for (int j = i; j < num_records; j++) {
                if (records[j].permit_number == records[i].permit_number) {
                    printf("%d %d %d:%d %d:%d\n", records[j].permit_number, records[j].lot_index,
                           records[j].entry_hour, records[j].entry_minute, records[j].exit_hour, records[j].exit_minute);
                    printed[j] = 1; // Mark as printed
                } else {
                    break;
                }
            }
        }
    }

    free(printed);
}

// Calculate and print the median duration for each lot
void process_median_durations(ParkingRecord *records, int num_records, int num_lots) {
    int **durations_per_lot = (int **)malloc(num_lots * sizeof(int *));
    int *count_per_lot = (int *)calloc(num_lots, sizeof(int));

    // Allocate and initialize arrays for each lot
    for (int i = 0; i < num_lots; i++) {
        durations_per_lot[i] = (int *)malloc(num_records * sizeof(int));
    }

    // Fill each lot's array with parking durations
    for (int i = 0; i < num_records; i++) {
        calculate_duration(&records[i]);
        int lot = records[i].lot_index;
        durations_per_lot[lot][count_per_lot[lot]++] = records[i].duration;
    }

    // Sort and calculate median for each lot's duration array
    for (int i = 0; i < num_lots; i++) {
        if (count_per_lot[i] > 0) {
            mergeSort((int *)durations_per_lot[i], 0, count_per_lot[i] - 1, 2, 1);

            int middle = count_per_lot[i] / 2;
            double median;
            if (count_per_lot[i] % 2 == 0) { // Even count, average middle values
                median = (durations_per_lot[i][middle - 1] + durations_per_lot[i][middle]) / 2.0;
            } else { // Odd count, use middle value
                median = durations_per_lot[i][middle];
            }
            printf("%d %.6f\n", i, median);
        } else {
            printf("%d 0.000000\n", i);
        }
    }

    // Free allocated memory for each lot's duration array
    for (int i = 0; i < num_lots; i++) {
        free(durations_per_lot[i]);
    }
    free(durations_per_lot);
    free(count_per_lot);
}

// Calculate maximum occupancy at any given time in the parking lot
void process_max_occupancy(ParkingRecord *records, int num_records) {
    int *entry_times = (int *)malloc(num_records * sizeof(int));
    int *exit_times = (int *)malloc(num_records * sizeof(int));

    // Convert entry and exit times to minutes since midnight
    for (int i = 0; i < num_records; i++) {
        entry_times[i] = records[i].entry_hour * 60 + records[i].entry_minute;
        exit_times[i] = records[i].exit_hour * 60 + records[i].exit_minute;
    }

    // Sort both entry and exit times
    mergeSort(entry_times, 0, num_records - 1, 0, 1);
    mergeSort(exit_times, 0, num_records - 1, 0, 1);

    int max_occupancy = 0, current_occupancy = 0;
    int i = 0, j = 0;

    // Calculate occupancy based on entry and exit events
    while (i < num_records && j < num_records) {
        if (entry_times[i] <= exit_times[j]) { // Entry event
            current_occupancy++;
            if (current_occupancy > max_occupancy) {
                max_occupancy = current_occupancy;
            }
            i++;
        } else { // Exit event
            current_occupancy--;
            j++;
        }
    }

    printf("%d\n", max_occupancy);

    // Free allocated memory
    free(entry_times);
    free(exit_times);
}

// Determine the number of unique lots by finding the highest lot index
int get_number_of_lots(ParkingRecord *records, int num_records) {
    int max_lot_index = -1;
    for (int i = 0; i < num_records; i++) {
        if (records[i].lot_index > max_lot_index) {
            max_lot_index = records[i].lot_index;
        }
    }
    return max_lot_index + 1;  // Lot indices start at zero
}

// Main function to handle file input, process modes, and output results
int main(int argc, char *argv[]) {
    if (argc < 3) { // Check for correct usage
        printf("Usage: %s <input file> <mode>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) { // Check if file opened successfully
        printf("Error opening file.\n");
        return 1;
    }

    int num_records;
    fscanf(file, "%d", &num_records);

    ParkingRecord *records = (ParkingRecord *)malloc(num_records * sizeof(ParkingRecord));
    for (int i = 0; i < num_records; i++) {
        fscanf(file, "%d:%d %d:%d %d %d", &records[i].entry_hour, &records[i].entry_minute,
               &records[i].exit_hour, &records[i].exit_minute, &records[i].lot_index, &records[i].permit_number);
    }

    // Process based on mode: duplicates, median durations, or max occupancy
    if (strcmp(argv[2], "p") == 0) {
        process_duplicates(records, num_records);
    } else if (strcmp(argv[2], "d") == 0) {
        int num_lots = get_number_of_lots(records, num_records);  // Determine unique lots
        process_median_durations(records, num_records, num_lots);
    } else if (strcmp(argv[2], "o") == 0) {
        process_max_occupancy(records, num_records);
    }

    // Free allocated memory and close the file
    free(records);
    fclose(file);
    return 0;
}
