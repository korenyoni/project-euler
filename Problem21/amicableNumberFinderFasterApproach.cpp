#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include "sieveOfAtkin/atkin.hpp"

std::vector<int> allPrimesUpToNumber;
std::vector<bool> allPrimesUpToNumberBool;
/* find all prime factors of a number */
std::unordered_map<int,int> findPrimeFactorsExponentMap(int number)
{
    std::unordered_map<int,int> primeFactors;
    for (int i = 0; (unsigned long)i < allPrimesUpToNumber.size(); i++)
        // stop if the number is a prime
        // or we've traversed through all the primes
    {
        int prime = allPrimesUpToNumber[i];
        int exponent = 0;
        while (number % prime == 0)
        {
            exponent++;
            number /= prime;
        }
        if (exponent > 0)
        {
            primeFactors.insert(std::pair<int,int>(prime, exponent));
        }
    }
    return primeFactors;
}
/* method that returns the number to the power of something */
int numberToPower(int base, int power)
{
    int result = base;
    if (power == 0)
    {
        return 1;
    }
    while (power > 1)
    {
        result *= base;
        power--;
    }
    return result;
}
/* returns sum of all the proper divisors of the number */
// iterate through each prime.
// get the sum of the prime's values starting from the number
// raised to its power as it is in the number's prime factorization
// down to the prime to the power of 0
// then multiply this sum for every prime factor of the number.
// this will give the sum of all the proper divisors of the number
// since we multiply all possible powers of each prime factor
// by each other
long findProperDivisorsSum(int number)
{
    long properDivisorsSum = 1;
    std::unordered_map<int,int> primeFactorsExponentMap = findPrimeFactorsExponentMap(number);
    std::unordered_map<int,int>::iterator it = primeFactorsExponentMap.begin();
    while (it != primeFactorsExponentMap.end())
            {
        int thisPrimeTerm = 0;
        int prime = (*it).first;
        int power = (*it).second;
        while (power >= 0)
        {
            thisPrimeTerm += numberToPower(prime,power);
            power--;
        }
        // multiply this prime factor's sum of itself at all exponents
        // by the proper divisor sum
        properDivisorsSum *= thisPrimeTerm;
        ++it;
    }
    return properDivisorsSum - number;
    // since we are considering only proper divisors,
    // we have to subtract the number itself
}
/* returns true if the specified map contains the specified key */
// complexity is constant (:
bool keyExists(std::unordered_map<int,int> &unorderedMap, int key)
{
    bool keyNotFound = unorderedMap.find(key) == unorderedMap.end();
    // if the key does not lead to a hashed container in the unordered_map
    // find(key) returns unorderedMap.end() (past-the-end element)
    return !keyNotFound;
}
long sumAmicableNumbers(std::unordered_map<int,int> &numberAndProperDivisorSum, int numberStart, int numberLimit)
{
    long sumAmicableNumbers = 0;
    while (numberStart < numberLimit)
    {
        int numberProperDivisorSum = numberAndProperDivisorSum[numberStart];
        // the sum of the number's proper divisors
        if (keyExists(numberAndProperDivisorSum, numberProperDivisorSum) && numberAndProperDivisorSum[numberProperDivisorSum] == numberStart
                && numberStart != numberProperDivisorSum)
            // if there is a key in the unordered map for the number's sum
            // and the sum of that sum's proper divisors are the same as number which gave
            // us this sum
            // and also, the number sum is not the same as the number, then we have an amicable number
        {
            sumAmicableNumbers += numberStart;
            std::cout << "Amicable number: " << numberStart;
            std::cout << ", its pair number: " << numberProperDivisorSum << std::endl;
        }
        numberStart++;
    }
    return sumAmicableNumbers;
}
/* populate the unordered map with the number as the key and its value being its sum of proper divisors */
void populateNumberProperDivisorMap(std::unordered_map<int,int> &numberAndProperDivisorSum, int start, int limit)
{
    for (int i = start; i < limit; i++)
    {
        int divisorSum = findProperDivisorsSum(i);
        numberAndProperDivisorSum.insert(std::pair<int,int>(i, divisorSum));
    }
}
/* main */
int main(int argc, const char * argv[])
{
    // do not start the program unless the parameters are valid
    int start = 0;
    int limit = 0;
    bool invalidParams = false;
    try
    {
        start = std::stoi(argv[1]);
        limit = std::stoi(argv[2]);
    }
    catch (std::logic_error)
    {
        invalidParams = true;
        std::cout << "Usage: amicableNumberFinder [beginNumber] [limitNumber(not inclusive)]" << std::endl;
    }
    // print any unneeded parameters the user provided
    if (argc > 3)
    {
         for (int i = 3; i < argc; i++)
         {
             std::cout << "Unneeded parameter: " << argv[i] << " " << std::endl;
         }
    }
    if (!invalidParams)
    {
        allPrimesUpToNumber = atkin(limit);
        allPrimesUpToNumberBool = boolAtkin(limit);
        std::unordered_map<int,int> numberAndProperDivisorSum;
        populateNumberProperDivisorMap(numberAndProperDivisorSum, start, limit);
        // output:
        std::cout << "Sum of all amicable numbers starting from " << start << " and under " << limit
        << ": " << sumAmicableNumbers(numberAndProperDivisorSum, start, limit) << std::endl;
    }
}
