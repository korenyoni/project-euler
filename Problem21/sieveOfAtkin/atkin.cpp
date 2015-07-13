#include "atkin.hpp"
#include <cstdio>
#include <vector>
#include <cmath>

/* methods used to test the prime candidates */
// each of these methods represents a quadratic formula used to test
// for a prime candidate:
// n =...
// 4x^2 + y^2 if n % 12 == 1 or 5
// 3x^2 + y^2 if n % 12 == 7
// 3x^2 - y^2 if n % 12 == 11
// these methods return true if x and y produce a prime candidate
void testFirstQuadratic(int x, int y, int limit, std::vector<bool> &primeIndexBoolVector)
{
    int n = (4 * x * x) + (y * y);
    bool isPrimeCandidate = n <= limit && (n % 12 == 1 || n % 12 == 5);
    if (n < primeIndexBoolVector.size() - 1)
    {
        primeIndexBoolVector[n] = primeIndexBoolVector[n] || isPrimeCandidate;
    }
}
void testSecondQuadratic(int x, int y, int limit, std::vector<bool> &primeIndexBoolVector)
{
    int n = (3 * x * x) + (y * y);
    bool isPrimeCandidate = n <= limit && (n % 12 == 7);
    if (n < primeIndexBoolVector.size() - 1)
    {
        primeIndexBoolVector[n] = primeIndexBoolVector[n] || isPrimeCandidate;
    }
}
void testThirdQuadratic(int x, int y, int limit, std::vector<bool> &primeIndexBoolVector)
{
    int n = (3 * x * x) - (y * y);
    bool isPrimeCandidate = x > y && n <= limit && (n % 12 == 11);
    if (n < primeIndexBoolVector.size() - 1)
    {
        primeIndexBoolVector[n] = primeIndexBoolVector[n] || isPrimeCandidate;
    }
}
/* filters multiples of numbers in the range 5 and limitSqrt */
// filtering out these numbers will leave us with prime numbers only
// we begin at five because the sieve of atkin does not work for prime numbers under 5
// and any multiples of numbers under 5 are composite numbers.
void filterMultiples(int limit, std::vector<bool> &primeIndexBoolVector)
{
    int limitSqrt = std::sqrt(limit);
    int n = 0;
    for (int filter = 5; filter <= limitSqrt; filter++)
    {
        for (int multiplyFilterBy = 2; multiplyFilterBy <= limitSqrt; multiplyFilterBy++)
        {
            n = filter * multiplyFilterBy;
            if (n < limit)
            {
                primeIndexBoolVector[n] = false;
            }
        }
    }
}
/* produces the prime vectors */
void producePrimeCandidates(std::vector<bool> &primeIndexBoolVector, int limit)
{
    int limitSqrt = std::sqrt(limit);
    // iterating x and y from 1 up to the square root of the limit
    // in a nested loop, plugging them into three quadratic equations
    // and checking their remainder against specific numbers will
    // produce all the prime candidates that we need
    for (int x = 1; x <= limitSqrt; x++)
    {
        for (int y = 1; y <= limitSqrt; y++)
        {
            testFirstQuadratic(x, y, limit, primeIndexBoolVector);
            testSecondQuadratic(x, y, limit, primeIndexBoolVector);
            testThirdQuadratic(x, y, limit, primeIndexBoolVector);
        }
    }
}
/* returns a boolean vector whose indeces represent numbers,
 * and their value is true if they are prime numbers*/
std::vector<bool> boolAtkin(int limit)
{
    std::vector<bool> primeIndexBoolVector(limit);
    // in this vector the prime number is the index
    // and the value is true if that index represents a prime number.
    producePrimeCandidates(primeIndexBoolVector, limit);
    filterMultiples(limit, primeIndexBoolVector);
    // populate primeNumbersVector with prime numbers
    // since the sieve of atkin does not work for primes under 5,
    // we have to add those numbers manually
    primeIndexBoolVector[2] = true;
    primeIndexBoolVector[3] = true;
    return primeIndexBoolVector;
}
/* returns a vector of all the prime numbers, in order,
 * less than or equal to the specified maximum */
std::vector<int> atkin(int limit)
{
    std::vector<bool> primeIndexBoolVector = boolAtkin(limit);
    std::vector<int> primeNumbersVector;

    for (int i = 0; i < primeIndexBoolVector.size(); i++)
    {
        if (primeIndexBoolVector[i])
        {
            primeNumbersVector.push_back(i);
        }
    }
    // this vector contains the prime numbers, in order.
    return primeNumbersVector;
}
