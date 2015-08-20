#include <cstdio>
#include <map>
#include <vector>
#include "primeNumberTools.hpp"
#include "../sieveOfAtkin/atkin.hpp"

/* return all the prime factors of the specified number and their exponent
 * as a prime factor of the number.*/
std::map<int,int> getPrimeFactorsExponentMap(int number)
{
    int sieveOfAtkinLimit = number < 5 ? 5 : number;
    // if the number is less than 5, make it 5.
    // this is because the sieve of Atkin does not work for primes
    // that are less than 5.
    std::map<int,int> primeFactorAndExponentMap;
    std::vector<bool> primeIndexBoolVector = boolAtkin(sieveOfAtkinLimit);
    std::vector<int> primesUnderNumberVector = atkinFromBoolVector(primeIndexBoolVector);
    int prime = 0;
    for (int i = 0; prime < number && i < primesUnderNumberVector.size(); i++)
    {
        bool isFactor = false;
        prime = primesUnderNumberVector[i];
        int dividedNumber = number;
        int power = 0;
        while (dividedNumber != 0 && dividedNumber % prime == 0)
        {
            isFactor = true;
            power++;
            dividedNumber /= prime;
        }
        if (isFactor) primeFactorAndExponentMap.insert(std::pair<int,int>(prime,power));
    }
    return primeFactorAndExponentMap;
}
