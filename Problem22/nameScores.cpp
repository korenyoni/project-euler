#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>

const char DOUBLE_QUOTE = '\"';
const char SUBTRACT_FROM_CHAR = 64;
const std::string NO_FILE_NAME_SPECIFIED_ERROR("Error: no files name specified!");
const std::string USAGE("Usage: nameScoresNoMap [namesFileName]");
// the ASCII value of A is 65, but to get it's value as an alphabetical char
// we need to subtract 64 from it.
/* read from the file and populate the name score map */
// this is an ordered map so the map will be in order
void populateNameMap(std::string fileName, std::map<std::string,int> &nameScoreMap)
{
    std::fstream fs(fileName.c_str(), std::fstream::in);
    std::string currentName;
    bool quotesAreOpen = false;
    char currentChar;
    int currentNameCharTotal = 0;
    // each name is between double quotes
    while (fs >> currentChar)
    {
        if (currentChar == DOUBLE_QUOTE)
        {
            quotesAreOpen = !quotesAreOpen;
            if (!quotesAreOpen)
            {
                nameScoreMap.insert(std::pair<std::string,int>(currentName,currentNameCharTotal));
            }
            else
                // the loop reached opening double quotes
                // i.e. another name
            {
                currentNameCharTotal = 0;
                currentName.clear();
            }
        }
        else if (quotesAreOpen && currentChar != DOUBLE_QUOTE)
        {
            currentName.push_back(currentChar);
            currentNameCharTotal += currentChar - SUBTRACT_FROM_CHAR;
        }
    }
}
/* calculate total name scores */
// the name score is the sum of character values in a name,
// multiplied by it's position on the list, starting at 1
long calculateTotalNameScores(std::map<std::string,int> &nameScoreMap)
{
    long totalNameScores = 0;
    int namePosition = 0;
    int currentNameCharTotal = 0;
    int currentNameScore = 0;
    std::map<std::string,int>::iterator it = nameScoreMap.begin();
    while (it != nameScoreMap.end())
    {
        namePosition++;
        currentNameCharTotal = (*it).second;
        currentNameScore = currentNameCharTotal * namePosition;
        (*it).second = currentNameScore;
        std::cout << (*it).first << ": " << (*it).second << std::endl;
        // output each name with it's namescore
        ++it;
        totalNameScores += currentNameScore;
    }
    return totalNameScores;
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
    std::map<std::string,int> nameScoreMap;
    populateNameMap(fileName, nameScoreMap);
    std::cout << calculateTotalNameScores(nameScoreMap) << std::endl;
}
