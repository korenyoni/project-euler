#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

const char DOUBLE_QUOTE = '\"';
// names are surrounded by double quotes
const int SUBTRACT_FROM_CHAR = 64;
// the alphabetical position of each character
// can be determined by subtracting 64 from it's ASCII value.
// this is because all the characters are uppercase
// and 'A's ASCII value is 65
const std::string NO_FILE_NAME_SPECIFIED_ERROR("Error: no files name specified!");
const std::string USAGE("Usage: nameScoresNoMap [namesFileName]");
/* read the names and populate the vector they will be stored in */
void populateNamesVector(std::string fileName, std::vector<std::string> &unsortedNamesVector)
{
    char currentChar;
    bool quotesAreOpen = false;
    std::string currentName;
    std::fstream fs(fileName.c_str(), std::fstream::in);
    while (fs >> currentChar)
    {
        if (currentChar == DOUBLE_QUOTE)
        {
            quotesAreOpen = !quotesAreOpen;
            if (!quotesAreOpen)
                // if the quotes are closed and we reach another set of double quotes
                // i.e. we reached the end of a name
            {
                unsortedNamesVector.push_back(currentName);
                currentName.clear();
            }
        }
        else if (quotesAreOpen)
            // if the quotes are open but we do not have double quotes
        {
            currentName.push_back(currentChar);
        }
    }
}
/* returns < 0 if stringA is lexicographically < string B */
// returns 0 if stringA is lexicographically equal to stringB
// returns > 0 if string A is lexicographically > string B
// in terms of alphabetical order
// e.g. stringCompare("bob", "zack") returns < 0
int stringCompare(std::string stringA, std::string stringB)
{
    int lengthStringA = stringA.length();
    int lengthStringB = stringB.length();
    // compare the two strings, character by character in a loop until we reach
    // the end of one of the strings
    // if the differenceStringAToStringB is negative, string A is lexicographically smaller
    // than String B. if it is 0, then they are equal. If it is positive, then String A is lexicographically
    // bigger than String B.
    // if they were equal until one of the strings ran out of characters, the longer string is lexicographically
    // larger than the other string
    char stringAchar = 0;
    char stringBchar = 0;
    for (int i = 0; stringAchar == stringBchar && i < std::max(lengthStringA,lengthStringB); i++)
    {
        stringAchar = (unsigned long)i < stringA.size() ? stringA[i] : 0;
        stringBchar = (unsigned long)i < stringB.size() ? stringB[i] : 0;
    }
    return stringAchar - stringBchar;
}
void addAllElements(std::vector<std::string> &vectorToAddTo, std::vector<std::string> &vectorToAdd)
{
    int vectorToAddSize = vectorToAdd.size();
    for (int i = 0; i < vectorToAddSize; i++)
    {
        vectorToAddTo.push_back(vectorToAdd[i]);
    }
}
/* using the quick sort algorithm, sort all the names in lexicographic order */
std::vector<std::string> quickSortNamesVector(std::vector<std::string> &unsortedNamesVector)
{
    unsigned long pivotIndex = unsortedNamesVector.size() / 2;
    std::vector<std::string> baseCaseVector;
    if (unsortedNamesVector.empty())
    {
        return baseCaseVector;
    }
    std::string nameAtPivot = unsortedNamesVector[pivotIndex];
    std::vector<std::string> leftVector;
    std::vector<std::string> rightVector;
    // compare each string in the unsorted list
    // if it is less than or equal to the name at the pivot, put it in a left vector
    // do the opposite if it is greater than the name at the pivot.
    for (unsigned long index = 0; index < unsortedNamesVector.size(); index++)
    {
        std::string nameAtIndex = unsortedNamesVector[index];
        if (index != pivotIndex)
        {
            stringCompare(nameAtIndex, nameAtPivot) <= 0 ?
            leftVector.push_back(nameAtIndex) : rightVector.push_back(nameAtIndex);
        }
    }
    std::vector<std::string> recursiveLeftVector = quickSortNamesVector(leftVector);
    std::vector<std::string> recursiveRightVector = quickSortNamesVector(rightVector);
    addAllElements(baseCaseVector, recursiveLeftVector);
    baseCaseVector.push_back(nameAtPivot);
    addAllElements(baseCaseVector, recursiveRightVector);
    return baseCaseVector;
}
/* MAIN */
int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << NO_FILE_NAME_SPECIFIED_ERROR << std::endl;
        std::cout << USAGE << std::endl;
    }
    std::string fileName(argv[1]);
    std::vector<std::string> unsortedNamesVector;
    // vector used to store the names in the list
    populateNamesVector(fileName, unsortedNamesVector);
    std::vector<std::string> sortedNamesVector = quickSortNamesVector(unsortedNamesVector);
    long totalNameScores = 0;
    for (unsigned long i = 0; i < sortedNamesVector.size(); i++)
    {
        std::string currentName = sortedNamesVector[i];
        int currentNameScore = 0;
        for (unsigned long charIndex = 0; charIndex < currentName.size(); charIndex++)
        {
            currentNameScore += currentName[charIndex] - SUBTRACT_FROM_CHAR;
        }
        totalNameScores += currentNameScore * (i + 1);
    }
    std::cout << totalNameScores << std::endl;
}
