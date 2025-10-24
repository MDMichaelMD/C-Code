// stdio.h provides I/O functions such as `scanf` and `printf`
#include <stdio.h>
// stdlib.h provides the atoi() and atof functions
#include <stdlib.h>

// Include the encounters.h header file, which contains the function definitions for functions
// implemented in encounters.c.
#include "encounters.h"





/**
 * The main function is called when the program is run. A return value of 0 indicates the program
 * ran successfully, while a non-zero return value indicates otherwise. The return value of the main
 * function in C corresponds to the "exit code" of the program.
 */
int main(int argc, char** argv) {
    int gridLength, num_animals, num_iterations;
    double p;
    unsigned int seed;


    /* Check if the number of arguments is valid */
    if (argc != 6) {
        printf("Wrong number of command-line arguments\n");
        return 1;
    }

    /* Read Input */
    gridLength = atoi(argv[1]);
    num_animals = atoi(argv[2]);
    num_iterations = atoi(argv[3]);
    p = atof(argv[4]);
    seed = atoi(argv[5]);

    /* Print error message if any of the values are invalid. */
    int flag = 0;
    
    if (gridLength<= 0) {
        printf("gridLength needs to be a positive integer\n");
        flag += 1;
    }
    if (num_animals <= 0) {
        printf("Number of animals needs to be a positive integer\n");
        flag += 1;
    }
    if (num_iterations <= 0) {
        printf("Number of timesteps needs to be a positive integer\n");
        flag += 1;
    }
    if (p < 0 || p > 1) {
        printf("Probability needs to be within [0, 1]\n");
        flag += 1;
    }
    if (flag > 0) { return 1; }


    /* Run Simulation */
    int num_encounters = encounters(gridLength, num_animals, num_iterations, p, seed);
    printf("%d\n", num_encounters);

    /* Exit */
    return 0;
}
