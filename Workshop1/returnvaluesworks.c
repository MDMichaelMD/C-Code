#include "returnvalues.h"
#include "math.h"

//goal create an array of 1000 nonnegative double values
void approach1(double p, double* maxval, int* maxidx) 
{
    double array[1000]; //creates an array of 1000 doubles
    int i = 0;  // loop index
  //for (; i <1000; 1++ // while the i starts off 
   while (i < 1000) // no ;
    {
        array[i] = pow(sin(p*i) , 2); // based on instructions 
        if (i == 0)
        { 
            *maxval = array[i];// defined the starting max
            *maxidx = i; // ini maxidi with index zero
        }
        if (array[i] > *maxval)
        {
            *maxval = array[i]; //update maxval if greater
            *maxidx = i; //update i to current greater
        }
i++; // increment and below to prevent needing a break
    }  
    
}
double approach2(double p, int* maxidx) {
    double array[1000]; // create an array of 1000 
    double maxval = 0.0;// init max val to min ( 0.0)
    int i = 0;  // loop index
   while (i < 1000) // loop till 999
    {
        array[i] = pow(sin(p*i) , 2); // based on instructions 
            if (i == 0)
            { 
                maxval = array[i]; //start value of max
                *maxidx = i; // inital max ind
            }
            if (array[i] > maxval) // compare each value
            {
                maxval = array[i]; //update maxval if greater
                *maxidx = i; //update i to current greater
            }


i++; // increment and below to prevent needing a break

    }
    return maxval; // return the maximum value
}

// See the header file (`returnvalues.h`) for the definition of MaxStruct.
MaxStruct approach3(double p) 
{
double array[1000]; //creates array of 1000 doubles
MaxStruct ms; //declares a struct 
ms.maxval = 0.0;// starting value double
ms.maxidx = 0; // starts 0 value int
int i = 0; // Initialize i in approach3

   while (i < 1000) // loop till 0 to 999
    {
        array[i] = pow(sin(p*i) , 2); // based on instructions 
            if (i == 0)
            { 
                ms.maxval = array[i]; //start value of max
                ms.maxidx = i; // inital max ind
            }
            if (array[i] > ms.maxval) // compare each value
            {
                ms.maxval = array[i]; //update maxval if greater
                ms.maxidx = i; //update i to current greater
            }
i++; // increment and below to prevent needing a break

    }
    return ms;
}
