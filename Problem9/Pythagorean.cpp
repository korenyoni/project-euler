#include <stdio.h>
#include <iostream>
#include <cmath>

/*MAIN*/
int main()
{
    int a, b; // declare a and b
    double c; // the c value for a*a + b*b = c*c
    int product = 0; // the value the product will be stored in

    a = 0;
    b = 0;

    // loop from 0 to 1000
    // increment a each time
    // nested loop to increment b each time, but for the main loop, only loop while a > b
    for (; a < 1000; b++)
    {
        for (a = 1; a < b ; a++) // start at 1, make sure a < b
        {
            c = std::sqrt(a * a + b * b); // compute the square root of a^2 + b^2
            if ((int)c >= c && c + a + b == 1000)
                // if the c is a perfect square
                // if a + b + c are equal to 1000
            {
                product = a * b * c;
            }
        }
    }
    std::cout << product << std::endl; // print the product
}
