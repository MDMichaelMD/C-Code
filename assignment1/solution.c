#include <math.h>
#include <stdio.h>
#include "solution.h"

//my variables

#define G 6.6743e-20 // Gravitational constant unit km^3/(kg s^2)
#define M 5.9722e24 // Earth's Mass KG
#define R 6378.1 // Earth's radius km

/**
 * Return `0` if the provided orbit heights are valid, or any non-zero integer (e.g. `1`) if the
 * provided orbit heights are not valid.
 *
 * Inputs: `di` is the initial orbit height and `df` is the target orbit height.
 */
int check_input_validity(double di, double df) //check if my inputs are valid
{
    if (di > 0 && df > 0 ) //the orbits should be above crashing they can be the same or drive on surface thats ok
    {
        return 0; //true
    }
    return 1; //false --you die you crash
       
    // TODO: Implement this function and return the correct value.
 
}

/**
 * Return the initial change in velocity required to initiate the transfer orbit.
 *
 * Inputs: `di` is the initial orbit height and `df` is the target orbit height.
 */
double get_initial_velocity_change(double di, double df) 
{
    //first start from the distance from earth's center

    double r1 = di + R; // Initial orbital radius from earth's core
    double r2 = df + R; // Final orbital radius from earth's core
    //we already checked if the inputs are valid so just plug into the first Vi change with the variables
    double a = (r1+r2) * .5 ; // Semi-major axis of the transfer orbit
    double v1 = sqrt((G * M ) / r1); // Velocity of intial orbit
    double v_p = sqrt(G * M * (2 / r1 - 1 / a)); // Velocity at perigee for transfer orbit
    return v_p - v1; // first Change in velocity , output (final - intiall)
}

/**
 * Return the final change in velocity required to maintain the desired orbit.
 *
 * Inputs: `di` is the initial orbit height and `df` is the target orbit height.
 */
double get_final_velocity_change(double di, double df) {
    // TODO: Implement this function and return the correct value.
   
    double r1 = di + R; // Initial orbital radius from earth's core
    double r2 = df + R; // Final orbital radius from earth's core
    //we already checked if the inputs are valid so just plug into the first Vi change with the variables
    // didnt I just define r1 and r2 and a? ask ta
    double a = (r1+r2) * .5 ; // Semi-major axis of the transfer orbit
    double vf = sqrt((G * M ) / r2); // Velocity of intial orbit
    double v_a = sqrt(G * M * (2 / r2 - 1 / a)); // Velocity at perigee for transfer orbit
    return vf - v_a; // first Change in velocity , output (final - intiall)

}

/**
 * Return the transfer time.
 *
 * Inputs: `di` is the initial orbit height and `df` is the target orbit height.
 */
double get_time(double di, double df) 
{
    double r1 = di + R; // initial orbital radius
    double r2 = df + R; // check with ta if this is redu, idk how to check my workshpace values
    double P = atan(1); // plugged in pi... should I use ==?
    P = 4 * P; 
    double a = (r1+r2) * .5 ;
    double transfer_time = P * sqrt(pow(a, 3) / (G * M));//declaring the variable transfer time
    return transfer_time / 3600; // 3600 seconds in an hour unit conversion
}