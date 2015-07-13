#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>

/*Generates primes separately under a certain amount, then sums them up*/
const int elementsInArray = 1000; // how many boolean values will go in a single array
/*Returns sum of all primes under a certain amount */
long atkin(int limit)
{
    int limitSqrt = std::sqrt(limit);
    int n; // the result of the quadratic formulas
    bool first, second, third; // boolean values representing each quadratic formula and
    // the remainder that it must compute to be true

    // populate the int[] vector: each element is an array of 1000 boolean values
    int numberArrays = limit / elementsInArray;
    if (numberArrays * elementsInArray < limit) {numberArrays++;}; // if numberArrays got truncated, add the remainder
    std::vector<std::vector<bool> > primeArrays;
    primeArrays.resize(numberArrays);
    // resize all the nested boolean vectors
    for (int i = 0; i < numberArrays; i++)
    {
        primeArrays[i].resize(elementsInArray, false);
    }
    // the sieve of atkin only works for primes >= 5, so set values 2 and 3 manually
    primeArrays[0][2] = true;
    primeArrays[0][3] = true;
    /*The sieve (and its three quadratic formulas)*/
    for (int x = 1; x <= limitSqrt; x++)
    {
        for (int y = 1; y <= limitSqrt; y++)
        {
            /*First populate the set of primes*/

            // for each quadratic formula, we make sure the prime set does not contain n before we calculate the formula
            // first quadratic: 4x^2 + y^2 where the remainder for n / 12 is 1 or 5
            n = (4 * x * x) + (y * y);
            first = n < limit && (n % 12 == 1 || n % 12 == 5);
            if (first) {primeArrays[n / elementsInArray][n % elementsInArray] = true;};
            // second quadratic: 3x^2 + y^2 where n % 12 is 7
            n = (3 * x * x) + (y * y);
            second = n < limit && (n % 12 == 7);
            if (second) {primeArrays[n / elementsInArray][n % elementsInArray] = true;};
            // third quadratic: 3x^2 - y^2 where n % 12 is 11
            n = (3 * x * x) - (y * y);
            third = x > y && n < limit && (n % 12 == 11);
            if (third) {primeArrays[n / elementsInArray][n % elementsInArray] = true;};
        }
    }
    /*Filter out prime candidates that are actually multiples of values plugged into x and / or y*/
    for (int i = 5; i <= limitSqrt; i++)
    {
        if (primeArrays[i / elementsInArray][i % elementsInArray])
        {
            for (int s = i + i; s < limit; s += i)
            {
                primeArrays[s / elementsInArray][s % elementsInArray] = false;// if the number is a multiple of a prime;
                //it is composite and therefore not prime.
            }
        }
    }

    /*sum up all the primes*/
    long sum = 0;
    for (int i = 0; i < primeArrays.size(); i++)
    {
        for (int n = 0; n < elementsInArray; n++)
        {
            if (primeArrays[i][n])
            {
                sum += i * elementsInArray + n; // add the prime
                // the i * elementsInArray represents the prime in term of its thousands (for example 3973 is 3000)
                // the n represents whatever comes after (for example for 3973: 973)
            }
        }
    }
    return sum; // return the set
}
/*Main*/
int main()
{
    long sum = atkin(2000000);
    std::cout << sum << std::endl;
}
