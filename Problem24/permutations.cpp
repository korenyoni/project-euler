#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>

/*generate the permutations recursively*/
/*arguments: the vector, the digits, the first digits being carried over, and the length of the digits. E.g. 123 is length 3.*/
void generatePermutations(std::vector<int> &myVector, int digits, int carryOver, int length)
{
    if (length == 2)
    {
        myVector.resize(myVector.size() + 2);
        int lastDigit = digits % 10;
        // Reverse the order of the last two digits by truncating them from digits then adding them backwards.
        int reverseLastTwo = (lastDigit * 10) + digits / 10;
        myVector[myVector.size() - 2] = carryOver * 100 + digits;
        //replace the last two digits in reverse order
        myVector[myVector.size() - 1] = carryOver * 100 + reverseLastTwo;
    }
    else
    {
        // recursive calls to rearranged digits
        for (int i = 0; i < length; i++)
        {
            int divideBy = std::pow(10, length - (i + 1));
            // the remainder 10 of the number truncated by divideBy will be the digit at index i
            int currentDigit = (digits / divideBy) % 10;
            // get the current digit at index i
            int withoutDigit = ((digits / (divideBy * 10)) * divideBy) + digits % divideBy;
            // remove the current digit
            // i.e. remove everything including and after the currentDigit, then add everything you removed except for currentDigit
            int currentDigitFirst = currentDigit * std::pow(10, length - 1) + withoutDigit;
            // current digit is now the first digit
            // call std::pow(10, length - 1) because 123's first digit, for example represents a hundred value
            // the number's length is 3, but 10^3 is 1000, whereas we need only to have it 10^2
            // and 10^2 will be the number currentDigit has to be multiplied by in order to get it to appear first
            int firstDigit = currentDigitFirst / std::pow(10, length -1);
            int newCarryOver = carryOver * 10;
            newCarryOver += firstDigit;
            // add another digit to the carryOver
            currentDigitFirst %= (int)std::pow(10, length - 1);
            // remove the first digit
            generatePermutations(myVector, currentDigitFirst, newCarryOver, length - 1);
            // now make a recursive call
        }
    }
}
int main()
{
    // the vector that will store the permutations
    std::vector<int> permutations;
    generatePermutations(permutations,1234,0, 4);
    /*test*/
    for (int i = 0; i < permutations.size(); i++)
    {
        std::cout << permutations[i] << std::endl;
    }
}
