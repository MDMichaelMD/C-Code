#include <stdio.h>
#include <stdlib.h>
#include "encounters.h"

#define UP 10
#define DOWN 20
#define RIGHT 30
#define LEFT 40



/* Visualize grid on printline for debugging purposes */
void printGrid(int* grid, int gridLength) {
    int total_animools = 0;
    for (int i = 0; i < gridLength*gridLength; i++) {
        printf("%d ", grid[i]);
        total_animools += grid[i];
        if ((i + 1) % gridLength == 0 && i != 0) {
            printf("\n");
        }
    }
    printf("Total animools: %d", total_animools);
    printf("\n");
}


/* Determine the new location for an animal that is moving */
int move(double r, double p, int gridLength, int i) {
    double interval = (1-p) / 4.0;
    int x = i % gridLength; // Get horizontal value
    int y = (i - x) / gridLength; // Get depth value
    int dir;
    
    // printf("(%d, %d)\n", x, y);

    // Determine direction, reverse directions if new location is out of bounds
    if (r < p + interval) {
        dir = UP;
        y--;
        if (y < 0) {
            dir = DOWN;
            y += 2;
        }
    } else if (r < p + 2.0 * interval) {
        dir = DOWN;
        y++;
        if (y > gridLength - 1) {
            dir = UP;
            y -= 2;
        }
    } else if (r < p + 3.0 * interval) {
        dir = LEFT;
        x--;
        if (x < 0) {
            dir = RIGHT;
            x += 2;
        }
    } else if (r < p + 4.0 * interval) {
        dir = RIGHT;
        x++;
        if (x > gridLength - 1) {
            dir = LEFT;
            x -= 2;
        }
    }
    // switch(dir) {
    //     case 10: printf("UP\n"); break;
    //     case 20: printf("DOWN\n"); break;
    //     case 30: printf("RIGHT\n"); break;
    //     case 40: printf("LEFT\n"); break;
    // }
    // printf("Direction: %d\n", dir);
    // printf("(%d, %d)\n", x, y);
    return x + y*gridLength;
}

/* Count all elements of grid greater than 1. Counts up all the encounters in the grid */
int count_encounters(int* grid, int gridLength) {
    int output = 0;
    for (int i = 0; i < gridLength*gridLength; i++) {
        if (grid[i] > 1) {
            output++;
        }
    }
    // printf("encounters: %d\n", output);
    return output;
}

int encounters(int gridLength, int num_animals, int num_iterations, double p, unsigned int seed) {


    srand(seed);
    int encounters = 0;
    
    /* Create Grid */
    int* grid = (int*) calloc(gridLength*gridLength, sizeof(int)); //use calloc to initialize as zeros

    // Check if memory allocation was successful
    if (grid == NULL) {
        printf("Memory allocation failed!\n");
        return 1;  // Exit the program if allocation fails
    }

    /* Populate Grid with Animals*/
    for (int i = 0; i < num_animals; i++) {
        int x = rand() % gridLength;
        int y = rand() % gridLength;
        grid[x*gridLength + y] += 1;
    }
    encounters += count_encounters(grid, gridLength);
    printGrid(grid, gridLength);

    /* Run simulation */
    for (int t = 0; t < num_iterations; t++) {
        int* temp_grid = (int*) calloc(gridLength * gridLength, sizeof(int));
        for (int i = 0; i < gridLength*gridLength; i++) {
            int num = grid[i];
            for (int a = 0; a < num; a++) {
                // printf("grid[i]: %d, a=%d, i=%d, t=%d\n", grid[i], a, i, t);
                double r = (double) rand() / RAND_MAX ;
                if (r > p) {
                    grid[i]--; // remove current animal
                    int new_loc = move(r, p, gridLength, i);
                    temp_grid[new_loc]++; // move current animal to new location
                } else {
                    temp_grid[i]++;
                }
                
            }
        }
        // printGrid(temp_grid, gridLength);
        encounters += count_encounters(temp_grid, gridLength);
        free(grid);
        grid = temp_grid;
    }

    /* Free array memory */
    free(grid);
    /* Return number of encounters */
    return encounters;
}