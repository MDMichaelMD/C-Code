#include <stdio.h>  // Standard input-output library
#include <stdlib.h> // Used for atoi, atof, srand, malloc, rand max and srand()
#include <string.h> //memcpy

int main(int argc, char *argv[]) // main function 
{
    // Ensure correct number of arguments
    if (argc != 6) 
    {
        return 1; //if wrong end program
    }

    // Input arguments
    int gridL = atoi(argv[1]);      // Grid length
    int numAn = atoi(argv[2]);      // Number of animals
    int numIt = atoi(argv[3]);      // Number of iterations
    double stayProb = atof(argv[4]); // Stay probability  
    unsigned int seed = atoi(argv[5]); // Seed value cool saves memory size
    
    // Validate inputs inverse
    if (gridL <= 0 || numAn <= 0 || numIt <= 0 || stayProb < 0 || stayProb > 1)// keep it positive and stay prob btw 0 to 1
    {
        return 1; //end program
    }

    // Seed the random number generator Minecraft style:D
    srand(seed); // allows for predicatable randomness

    // Allocate memory for the grid as a 1D array
    int *grid = (int *)calloc(gridL * gridL, sizeof(int)); // array of zeros
    if (grid == NULL) // Check if memory allocation failed
    {
        return 1; // memory allocation failed, end program
    }
  
    // Animal positions (1D array where index corresponds to the grid index)
    int *animalX = (int *)malloc(numAn * sizeof(int)); // x coordinates
    int *animalY = (int *)malloc(numAn * sizeof(int)); // y coordinates
   
    if (animalX == NULL || animalY == NULL) //check if failure in memory allocation
    {
        free(grid); //free the memory
        return 1; // memory allocation failed, end program
    }

    // Randomly place animals on the grid
    for (int i = 0; i < numAn; i++) 
    {
        animalX[i] = rand() % gridL;
        animalY[i] = rand() % gridL; // gives me random values and takes remainder
        int index = animalX[i] * gridL + animalY[i];
        grid[index]++;  //grid[index]+1; // Increment grid cell where the animal is placed
    }

    int encounters = 0; //reset encounters for each iteration

    // Simulate the number of iterations via grid
    for (int x = 0; x < gridL; x++) //outer loop
    { 
        // Sweep over the grid and count initial encounters
        for (int y = 0; y < gridL; y++) //inner loop
        {
            int index = x * gridL + y;
            if (grid[index] > 1) //if more than one animal i any animal this is one encounter
            {
                encounters++; //cycle through
            }
        }
    }

    int *new_grid = (int *)calloc(gridL * gridL, sizeof(int)); // a new grid of each iteration
    if (new_grid == NULL) // Check if memory allocation failed
    {
        return 1; // memory allocation failed, end program
    }
    for ( int nuts = 0; nuts < numIt; nuts++) 
    {  // Simulate the number of iterations via grid
     
        for (int x = 0; x < gridL; x++) //outer loop
        { 
            // Sweep over the grid and count initial encounters
            for (int y = 0; y < gridL; y++) //inner loop
            {
                // int index = x * gridL + y;
                // if (grid[index] >= 1) //if more than one animal i any animal this is one encounter
                // {
                //     encounters++; //cycle through
                // }
                int a; //define variable number of animals in a block
                a=grid[x*gridL+y]; // number of aninal in this specific block
                // Move animals that are at this (x, y) position
                for (int i = 0; i < a; i++) // loop through the animals and update their positions
                {
                    //if (animalX[i] == x && animalY[i] == y) // check if the animal is already here
                   // {
                        double r = (double)rand() / RAND_MAX; // avoids integer/integer division
                        double probs = (1 - stayProb) / 4.0; // Corrected division to avoid integer division
                        int newX = x;
                        int newY = y;
                        if (r > stayProb) // if the random num is greater than stay prob, the animal will move
                        { 
                            if (stayProb + (3 * probs) <= r && r <= stayProb + (4 * probs))
                            { // Move North (up)
                                newY = (newY == gridL - 1) ? gridL - 2 : newY + 1; // Reflect if needed
                            } 
                            else if (stayProb + (2 * probs) <= r && r < stayProb + (3 * probs))
                            { // Move South (down)
                                newY = (newY == 0) ? 1 : newY - 1; // Reflect if needed
                                
                            } 
                            else if (stayProb + probs <= r && r < stayProb + (2 * probs))
                            { // Move East (right)
                                newX = (newX == gridL - 1) ? gridL - 2 : newX + 1; // Reflect if needed
                                
                            }
                            else if (stayProb <= r && r < stayProb + probs)
                            { // Move West (left)
                                newX = (newX == 0) ? 1 : newX - 1; // Reflect if needed
                                
                                
                            }

                            // Update grid: decrement the old position and increment the new one
                            //grid[animalX[i] * gridL + animalY[i]]--; // provided by assignment
                            new_grid[newX * gridL + newY]++; // increment the new position

                            // Update animal's position
                            animalX[i] = newX;
                            animalY[i] = newY;
                            //after newx and y could I make grab those values and compare them to my current i by i location?
                            //make current grid to be zero once I pass with encounter then only add to count on the new encount

                        }
                        else //new grid counts original and new location
                        {//update the information of the new grid
                            new_grid[newX * gridL + newY]++; //new grid location if it stays

// if it stays update new ggrid 
                        }
                   // }
                }
            }
        }
        ///copy the new grid to the old and overwrite then count the encounters on the update old grid
        /* int *new = (int *)calloc(gridL * gridL, sizeof(int)); // array of zeros
        if (grid == NULL) // Check if memory allocation failed
        {
            return 1; // memory allocation failed, end program
        }*/
        //make a new grid that is based off new locations only and count reencounterments
        for (int x = 0; x < gridL; x++) //outer loop
        { 
            // Sweep over the grid and count initial encounters
            for (int y = 0; y < gridL; y++) //inner loop
            {
                int index = x * gridL + y;
                grid[index] = new_grid[index];
                if (new_grid[index] > 1) //if more than one animal i any animal this is one encounter
                {
                    encounters++; //cycle through
                }
                new_grid[index] = 0;
            }
        }
    
    }
    printf("%d\n", encounters);

    // Free dynamically allocated memory
    free(grid);
    free(new_grid);
    free(animalX);
    free(animalY);

    return 0; // we are done, freed the memory and end the program
}
