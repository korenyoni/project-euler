#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

/*Generate permutations*/
void generatePermutations(std::vector<std::string> &myVector, std::string remainingChars, std::string carriedChars)
{
    // if there are only two chars left, then there are two permutations:
    // first: remaingChars appended to carriedChars
    // second: remainingChars in reverse order, appended to carriedChars
    if (remainingChars.size() == 2)
    {
        myVector.resize(myVector.size() + 2);
        std::string firstPermutation = carriedChars;
        std::string secondPermutation = carriedChars;
        // make the vector bigger by two, then instantiate two strings

        firstPermutation.append(remainingChars);
        // append the remaining chars to the first string

        std::string remainingCharsReverse(remainingChars);
        remainingCharsReverse[0] = remainingChars[1];
        remainingCharsReverse[1] = remainingChars[0];
        secondPermutation.append(remainingCharsReverse);
        // append a reversed version of tphe remaining chars to the second string

        myVector[myVector.size() - 2] = firstPermutation;
        myVector[myVector.size() - 1] = secondPermutation;
        // add the two strings (representing a permutation each) to the vector
    }
    // if there is more than two chars left, we need to replace the first char and make a recursive call
    // on the same string but without the first character
    else
    {
        for (int i = 0; i < remainingChars.size(); i++)
        {
            char firstChar = remainingChars[0];
            char indexChar = remainingChars[i];
            remainingChars[i] = firstChar;
            remainingChars[0] = indexChar;
            // swap the first char with the char at index i
            std::string firstCharRemoved = remainingChars.substr(1, remainingChars.size());
            std::string newCarriedChars = carriedChars;
            newCarriedChars.resize(newCarriedChars.size() + 1);
            newCarriedChars[newCarriedChars.size() - 1] = indexChar;
            // recursive call on a string with the first character removed, and the carried chars now has
            // the first character in the rearranged string appended to it
            generatePermutations(myVector, firstCharRemoved, newCarriedChars);
        }
    }
}
/*Recursive factorial method used to predict how many permutations there will be from a given string*/
int factorial(int stringSize)
{
    if (stringSize == 1)
    {
        return stringSize;
    }
    return stringSize * factorial(stringSize - 1);
}
/*Main*/
int main()
{
    std::vector<std::string> permutations;
    // the vector that will hold the permutations

    // prompt the user to enter the base permutation
    std::cout << "Enter the base permutation, in order (e.g. 0123): ";
    std::string basePermutation;
    std::cin >> basePermutation;

    // prompt the user for the permutation that they want
    unsigned int permutationNumber;
    std::cout << "Enter the permutation number that you would like: ";
    std::cin >> permutationNumber;

    // catch invalid inputs which would lead to segmentation faults
    if (basePermutation.size() < 2)
    {
        std::cout << std::endl << '"' << basePermutation << '"' << "  is one character long. It should be at least two characters long." << std::endl;
    }
    else if (permutationNumber >= factorial(basePermutation.size()))
    {
        std::cout << std::endl << "Invalid permutation number. Should be < len(base_permutation)! AND > 0." << std::endl
            << "The string entered has " << factorial(basePermutation.size()) << " permutations."
            << " You entered " << permutationNumber << std::endl;
        // this is pretty cool because if the user enters a negative integer, since the variable
        // permutationNumber is unsigned, it would wrap under and become a large integer.
        // and this leads to the error message being displayed, which accounts for both errors
    }
        else
        // if there are no invalid arguments, then we can calculate the permutations
    {
        generatePermutations(permutations, basePermutation, "");
        std::cout << std::endl << permutations[permutationNumber] << std::endl;
    }
}
