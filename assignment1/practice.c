#include <stdio.h>
#include <math.h> //no need but i want to practice writing


int main() //no input variable
{ //start the function
int age; //defined a integer variable labelled age without a value

    printf("enter the age"); //input script
    scanf("%d", &age);//it is reading an integer
    //valrprintf("Debug: Age is %d\n", age); // Check if age is set correctly
        if (age < 13)
        {
            printf("You are a child.");
        }
        else if (13 <= age && age <=19)
        {
            printf("You are a teenager");
        }
        else
        {
            printf("You are an adult.");
        }
        return 0; //end the code
 }
