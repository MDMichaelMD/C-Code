#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void initializeGrid(int *grid);
void placeAnimals(int *grid);
void countEncounters(int *grid);
void resetNextGrid(int *nextGrid);
void updateGrid(int *grid, int *nextGrid);

// Global variables
int gridLen;        // Length of the grid
int animalNum;      // Number of animals
int iterationsNum;  // Number of iterations
double stayProb;    // Probability of an animal staying in the same cell
int seedValue;      // Seed value for the random number generator
int encountNum = 0; // Number of encounters

// Function to initialize the grid with zeros
void initializeGrid(int *grid)
{
    for (int i = 0; i < gridLen * gridLen; i++)
    {
        grid[i] = 0;
    }
}

// Function to place animals randomly in the grid
void placeAnimals(int *grid)
{
    for (int i = 0; i < animalNum; i++)
    {
        int x = rand() % gridLen;
        int y = rand() % gridLen;
        grid[x * gridLen + y]++;
    }
}

// Function to count encounters in the grid
void countEncounters(int *grid)
{
    for (int i = 0; i < gridLen * gridLen; i++)
    {
        if (grid[i] > 1)
        {
            encountNum++;
        }
    }
}

// Function to reset the next grid (used for the next iteration)
void resetNextGrid(int *nextGrid)
{
    for (int i = 0; i < gridLen * gridLen; i++)
    {
        nextGrid[i] = 0;
    }
}

// Function to update the position of animals in the grid
void updateGrid(int *grid, int *nextGrid)
{
    // Iterate over the grid
    for (int i = 0; i < gridLen; i++)
    {
        for (int j = 0; j < gridLen; j++)
        {
            // If the cell is empty, skip it
            if (grid[i * gridLen + j] == 0)
            {
                continue;
            }
            // Move the animals in the cell
            while (grid[i * gridLen + j] > 0)
            {
                grid[i * gridLen + j]--;
                double p = (double)rand() / RAND_MAX;
                // Check if the animal stays in the same cell
                if (p < stayProb || gridLen == 1)
                {
                    nextGrid[i * gridLen + j]++;
                }
                // Move the animal to a neighboring cell
                else
                {
                    int x = i;
                    int y = j;
                    // Generate a random direction
                    if (p < stayProb + (1 - stayProb) / 4)
                    {
                        if (x - 1 < 0)
                            x += 1;
                        else
                            x -= 1;
                    }
                    else if (p < stayProb + 2 * (1 - stayProb) / 4)
                    {
                        if (x + 1 >= gridLen)
                            x -= 1;
                        else
                            x += 1;
                    }
                    else if (p < stayProb + 3 * (1 - stayProb) / 4)
                    {
                        if (y - 1 < 0)
                            y += 1;
                        else
                            y -= 1;
                    }
                    else
                    {
                        if (y + 1 >= gridLen)
                            y -= 1;
                        else
                            y += 1;
                    }
                    nextGrid[x * gridLen + y]++;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    // Check if the number of arguments is correct
    if (argc != 6)
    {
        return 1;
    }

    // Parse the arguments
    gridLen = atoi(argv[1]);
    animalNum = atoi(argv[2]);
    iterationsNum = atoi(argv[3]);
    stayProb = atof(argv[4]);
    seedValue = atoi(argv[5]);

    // Validate the arguments
    if (gridLen <= 0 || animalNum <= 0 || iterationsNum <= 0 || stayProb < 0 || stayProb > 1)
    {
        return 1;
    }

    // Seed the random number generator
    // convert seedValue to unsigned int
    srand((unsigned int)seedValue);

    // Allocate memory for the grid
    int *grid = (int *)malloc(gridLen * gridLen * sizeof(int));
    // Use nextGrid to store the next iteration, so that we can update the grid in place without affecting the current iteration
    int *nextGrid = (int *)malloc(gridLen * gridLen * sizeof(int));

    // Initialize and place animals on the grid
    initializeGrid(grid);
    placeAnimals(grid);

    // Iterate over the number of iterations
    for (int iter = 0; iter < iterationsNum; iter++)
    {
        countEncounters(grid);
        resetNextGrid(nextGrid);
        updateGrid(grid, nextGrid);
        memcpy(grid, nextGrid, gridLen * gridLen * sizeof(int));
    }

    // Count the encounters in the final grid
    countEncounters(grid);

    // Free memory and print the number of encounters
    free(grid);
    free(nextGrid);
    printf("%d\n", encountNum);

    return 0;
}
