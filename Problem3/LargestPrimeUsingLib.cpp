#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include "../lib/sieveOfAtkin/atkin.hpp"

const std::string USAGE("Usage: LargestPrimeUsingLib [number to find largest prime factor of]");

/* recursive method that will find the largest prime factor */
// if the prime is under or equal to the square root of the original number
// the method will immediately return that number.
// if the number is greater than the square root, the method will iterate through
// the entire loop and return that number, which is prime.
// In case the prime number is greater than the square root, it's other prime factors
// will have to be under the square root of the number, because it is impossible for a number n
// to have more than one prime factor greater than the square root of n.
// therefore this method is correct.
unsigned long maxPrimeFactor(long number, long squareRootNumber, std::vector<int> &primeNumberVector, std::vector<bool> &primeNumberIndexBoolVector)
{
    for (int i = 0; i < primeNumberVector.size(); i++)
    {
        int prime = primeNumberVector[i];
        //std::cout << "iteration: " << i << " number: " << number << std::endl;
        if (number % prime == 0)
        {
            number /= prime;
            if (number <= squareRootNumber && primeNumberIndexBoolVector[number]) return number;
            // if the number we got from dividing the original number by a prime factor is a prime,
            // it is the largest prime factor (since we begin dividing with the smallest prime factors)
            else return(maxPrimeFactor(number, squareRootNumber, primeNumberVector, primeNumberIndexBoolVector));
            // otherwise, make a recursive call to the divided number.
        }
    }
    return number;
}
/* MAIN */
int main(int argc, char * argv[])
{
    bool doNotRunAlgorithm = false;
    unsigned long numberToFactorize = 0;
    /* handle arguments */
    try
    {
        numberToFactorize = argc > 1 ? std::stol(argv[1]) : numberToFactorize;
    }
    catch (std::invalid_argument)
        // the argument in place of the number to factorize was not a valid
        // character string representation of an integer
    {
        doNotRunAlgorithm = true;
    }
    if (!doNotRunAlgorithm && argc == 2)
    {
        long squareRootNumber = std::sqrt(numberToFactorize);
        std::cout << "SQUARE ROOT: " << squareRootNumber << std::endl;
        std::vector<bool> primeNumberIndexBoolVector(boolAtkin(squareRootNumber));
        std::vector<int> primeNumberVector(atkinFromBoolVector(primeNumberIndexBoolVector));
        unsigned long maxPrimeFactorOfNumber = maxPrimeFactor(numberToFactorize, squareRootNumber, primeNumberVector, primeNumberIndexBoolVector);
        if (maxPrimeFactorOfNumber > 0) std::cout << "LARGEST PRIME FACTOR: " << maxPrimeFactorOfNumber << std::endl;
        else std::cout << "OVERFLOW (" << maxPrimeFactorOfNumber << ")" << std::endl;
    }
    else
        // the user did not provide the proper arguments
    {
        std::cout << USAGE << std::endl;
    }
}
