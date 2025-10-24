#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "model.h" // Include model.h for Node struct and related functions

// Function to parse input file
void parseInput(char *filename, int *dims, int *size, int *numIterations, int *regionExtent, double *initialValue, int *periodic) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d %d %d %d %lf %d", dims, size, numIterations, regionExtent, initialValue, periodic);
    fclose(file);
}

// Initialize the grid
Node* initializeGrid(int size, int dims, int regionExtent, double initialValue) {
    int totalSize = (dims == 1) ? size : size * size;
    Node *grid = (Node *)malloc(totalSize * sizeof(Node));

    // Initialize each node
    for (int i = 0; i < totalSize; i++) {
        initializeNode(&grid[i]);
    }

    // Set initial 'v' value for the specified region
    if (dims == 1) {
        for (int i = 0; i < regionExtent; i++) {
            grid[i].v = initialValue;
        }
    } else {
        for (int i = 0; i < regionExtent; i++) {
            for (int j = 0; j < regionExtent; j++) {
                grid[i * size + j].v = initialValue;
            }
        }
    }
    return grid;
}

// Calculate diffusion
double calculateDiffusion(Node *grid, int i, int j, int size, int dims, int periodic) {
    double diffusion = 0.0;
    
    // Define neighbors based on boundary conditions
    if (dims == 1) {
        int left = (i == 0) ? 1 : i - 1; // Reflect to the next element
        int right = (i == size - 1) ? size - 2 : i + 1; // Reflect to the previous element


        diffusion = grid[left].v + grid[right].v - 2 * grid[i].v;
    } else {
        int up = (i == 0) ? 1 : i - 1; // Reflect to the next row
        int down = (i == size - 1) ? size - 2 : i + 1; // Reflect to the previous row
        int left = (j == 0) ? 1 : j - 1; // Reflect to the next column
        int right = (j == size - 1) ? size - 2 : j + 1; // Reflect to the previous column



        diffusion = grid[up * size + j].v + grid[down * size + j].v +
                    grid[i * size + left].v + grid[i * size + right].v -
                    4 * grid[i * size + j].v;
    }
    return diffusion;
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <num threads>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int dims, size, numIterations, regionExtent, periodic;
    double initialValue;
    parseInput(argv[1], &dims, &size, &numIterations, &regionExtent, &initialValue, &periodic);
    int numThreads = atoi(argv[2]);

    Node *grid = initializeGrid(size, dims, regionExtent, initialValue);
    Node *newGrid = (Node *)malloc((dims == 1 ? size : size * size) * sizeof(Node));
    
    double startTime = omp_get_wtime();
#pragma omp parallel num_threads(numThreads)
{
    for (int iter = 0; iter < numIterations; iter++) {
        if (dims == 2) { // Collapse only for 2D grids
            #pragma omp for collapse(2)
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    int idx = i * size + j;
                    double diffusion = calculateDiffusion(grid, i, j, size, dims, periodic);
                    updateNode(&grid[idx], &newGrid[idx], diffusion);
                }
            }
        } else { // Single loop for 1D grids
            #pragma omp for
            for (int i = 0; i < size; i++) {
                int idx = i;
                double diffusion = calculateDiffusion(grid, i, 0, size, dims, periodic); // j=0 for 1D
                updateNode(&grid[idx], &newGrid[idx], diffusion);
            }
        }

        // Copy updated grid values back
        #pragma omp for
        for (int i = 0; i < size * (dims == 1 ? 1 : size); i++) {
            grid[i] = newGrid[i];
        }
    }
}

   // #pragma omp parallel num_threads(numThreads)
   /* {
        for (int iter = 0; iter < numIterations; iter++) 
        {
            #pragma omp for collapse
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < (dims == 1 ? 1 : size); j++) {
                    int idx = (dims == 1) ? i : i * size + j;
                    double diffusion = calculateDiffusion(grid, i, j, size, dims, periodic);
                    updateNode(&grid[idx], &newGrid[idx], diffusion);
                }
            }

            #pragma omp for
            for (int i = 0; i < size * (dims == 1 ? 1 : size); i++) {
                grid[i] = newGrid[i];
            }
        }
    }
*/
    double endTime = omp_get_wtime();
    printf("Time in parallel region: %f\n", endTime - startTime);

    // Output results with high precision matching the expected format
    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < size * (dims == 1 ? 1 : size); i++) {
        fprintf(outputFile, "%f\n", grid[i].v); // Adjust precision as needed
    }
    fclose(outputFile);

    // Clean up
    free(grid);
    free(newGrid);

    return 0;
}
