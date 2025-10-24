#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define FUNC(x) (4.0 / (1.0 + (x) * (x)))  // Define f(x) = 4 / (1 + x^2)
#define TRUE_PI M_PI  // Use M_PI constant from math.h for the value of pi

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_intervals> <num_threads>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    int num_intervals = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    double a = 0.0, b = 1.0;
    double h = (b - a) / num_intervals;  // Step size

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    double integral = 0.0;
    double start_time = omp_get_wtime();  // Start time for parallel section

    // Calculate the integral using OpenMP
    #pragma omp parallel for reduction(+:integral)
    for (int i = 0; i < num_intervals; i++) {
        double x_mid = a + (i + 0.5) * h;  // Midpoint of each interval
        integral += FUNC(x_mid);
    }

    integral *= h;  // Multiply by step size
    double end_time = omp_get_wtime();  // End time for parallel section

    // Calculate the error
    double error = TRUE_PI - integral;
    double elapsed_time = end_time - start_time;

    // Print results with required precision
    printf("%.15f\n", integral);
    printf("%.15f\n", error);
    printf("%f\n", elapsed_time);

    return 0;
}
