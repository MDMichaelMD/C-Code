#include "returnvalues.h"
#include <math.h>

void approach1(double p, double* maxval, int* maxidx) {
    // Create an array of 1000 nonnegative double values
    double arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = pow(sin(i * p), 2);
        if (i == 0) {
            *maxval = arr[i];   // Initialize maxval
            *maxidx = i;        // Initialize maxidx
        } else if (arr[i] > *maxval) { 
            *maxval = arr[i];   // Update maxval
            *maxidx = i;        // Update maxidx
        }
    }
}  // <-- Closing brace for approach1

double approach2(double p, int* maxidx) {
    double arr[1000];
    double maxval = 0.0;
    for (int i = 0; i < 1000; i++) {
        arr[i] = pow(sin(i * p), 2);
        if (i == 0) {
            maxval = arr[i];     // Initialize maxval
            *maxidx = i;         // Initialize maxidx
        } else if (arr[i] > maxval) {
            maxval = arr[i];     // Update maxval
            *maxidx = i;         // Update maxidx
        }
    }
    return maxval;
}

MaxStruct approach3(double p) {
    MaxStruct results;
    results.maxval = 0.0;
    results.maxidx = 0;
    double arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = pow(sin(i * p), 2);
        if (arr[i] > results.maxval) { 
            results.maxval = arr[i]; // Update maxval in struct
            results.maxidx = i;      // Update index in struct
        }
    }
    return results;
}
