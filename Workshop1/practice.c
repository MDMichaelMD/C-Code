#include <stdio.h>
#include <stdlib.h> // For malloc, calloc, and free
#include <math.h> //pow
#include <stdint.h> // for fixed width integers, uint32_t
void  powers(uint32_t *array, int sizeofarray)
  {
    for (int i = 0; i < sizeofarray; i++ ) //why cannt i be less than numElements
        {
            array[i] = (uint32_t)pow(base, i); // raise the array at i to the power of base
        }
  }
int main() //not quite sure, i believe the output will be an int for value
{
    //created my variable
    int numElements;
    int base;
    //input
    printf("Enter a integer for number of elements:");
    //scanf("%d %d", &numElements, &base); // two in one
    scanf("%d", &numElements);
    printf("Enter a integer for the base number:");
    scanf("%d", &base);


    //allocate memory with zeros
    uint32_t *power = calloc(numElements. sizeof(uint32_t)); //define a pointer value at power to be the calloc unsure about sizing though
        if (power ==NULL)
        {return 1;} //check if allocation was successful and if it fails exit it

    //populate the Arraywith powers
  powers(power, numElements, base); //creates a function for the void to access //will go to the helper function and once it ends it will return here
    
    //print the array
/*printf("array[%d] = %d\n", i , power[i]) ;//im stuck here
    for int i = o; i < numElements; i++)
        {
            printf("%d", power[i]);
        }
        printf("\n"); // creates a new line...could have been done within the for loop except at the end it would be missing
f*/
    // Print the array contents
    printf("Array of powers:\n");
    for (int i = 0; i < numElements; i++) {
        printf("array[%d] = %u\n", i, power[i]); // %u is used for uint32_t
    }
    printf("\n");

free(power);
return 0; //if success end the program
}
/* without special width costrints
#include <stdio.h>
#include <stdlib.h> // For malloc, calloc, and free
#include <math.h>   // For pow function

// Function to fill an array with powers of the base
void powers(int *array, int sizeofarray, int base) {
    for (int i = 0; i < sizeofarray; i++) {
        array[i] = (int)pow(base, i); // Calculate base^i and store it as an int
    }
}

int main() {
    int numElements;
    int base;

    // Ask the user for the number of elements
    printf("Enter an integer for the number of elements: ");
    scanf("%d", &numElements);

    // Ask the user for the base number
    printf("Enter an integer for the base number: ");
    scanf("%d", &base);

    // Allocate memory for an array of `numElements` integers, each initialized to 0
    int *power = calloc(numElements, sizeof(int));
    if (power == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit if allocation fails
    }

    // Populate the array with powers
    powers(power, numElements, base);

    // Print the contents of the array
    printf("Array of powers:\n");
    for (int i = 0; i < numElements; i++) {
        printf("array[%d] = %d\n", i, power[i]); // %d for int
    }
    printf("\n");

    // Free the allocated memory
    free(power);
    return 0;
}
*/