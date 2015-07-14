#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include "../libs/sieveOfAtkin/atkin.hpp"

std::vector<int> allPrimesUpToNumber;
std::vector<bool> allPrimesUpToNumberBool;
/* find all prime factors of a number */
std::set<int> findPrimeFactorsSet(int number)
{
    std::set<int> primeFactors;
    for (int i = 0; (unsigned long)i < allPrimesUpToNumber.size(); i++)
        // stop if the number is a prime
        // or we've traversed through all the primes
    {
        int prime = allPrimesUpToNumber[i];
        while (number % prime == 0)
        {
            primeFactors.insert(prime);
            number /= prime;
        }
    }
    return primeFactors;
}
/* recursive method that populates all the proper divisors of a number into a list */
// I divide a number by each of it's prime factors.
// at first, it'll be divisible by all the prime factors.
// I add the result to the set of the number's proper divisors
// the result is a combination of the original number's proper divisors
// I try to divide each result by the original number's prime factors again
// If there is no remainder and I get a result, I do the same for the result, for every prime factor
// of the original number again. Eventually, the result is no longer a composite number. Calling this method
// recursively gives me every combination of the original number's
// prime factors, less than the original number, i.e. the original number's proper divisors.
void allDivisors(int number, std::set<int> &divisorsSet, std::set<int> &primeFactorsSet)
{
    std::set<int>::iterator it = primeFactorsSet.begin();
    int primeFactor = *it;
    while (number > primeFactor && it != primeFactorsSet.end())
    {
        // iterate througb all the prime factors of the original number
        // if a number can be divided by that prime factor
        // we'll call the method on the number divided by the prime factor
        // and add that number, i.e. the proper divisor, to the set of proper divisors
        if (number % primeFactor == 0)
        {
            int result = number / primeFactor;
            // result is a combination of prime Factors for the original number
            divisorsSet.insert(result);
            allDivisors(result, divisorsSet, primeFactorsSet);
        }
        ++it;
        primeFactor = *it;
    }
}
/* call the recursive method allDivisors and return all the proper divisors of the specified number */
std::set<int> findProperDivisors(int number)
{
    std::set<int> properDivisorsSet;
    properDivisorsSet.insert(1);
    std::set<int> primeFactorsSet = findPrimeFactorsSet(number);
    allDivisors(number, properDivisorsSet, primeFactorsSet);
    return properDivisorsSet;
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
        int divisorSum = 0;
        std::set<int> numberProperDivisors = findProperDivisors(i);
        std::set<int>::iterator numberProperDivisorsIt = numberProperDivisors.begin();
        for (int divisor = 0; numberProperDivisorsIt != numberProperDivisors.end(); ++numberProperDivisorsIt)
        {
            divisor = *numberProperDivisorsIt;
            divisorSum += divisor;
        }
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
