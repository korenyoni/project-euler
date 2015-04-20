#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>

/*Used to test correctness of the vector*/
void print(std::vector<char> myVector)
{
    for (int i = 0; i < myVector.size(); i += 50) // represents a row
    {
        for (int j = 0; j < 50; j++) // iterate through each digit in the row
        {
            std::cout << myVector[i + j]; // print that element of the vector
        }
        std::cout << std::endl; // end the line on the 50th number
    }
}
int main()
{
    int PRODUCT_WIDTH = 13;
    int CHAR_SUBTRACT = 48; // the number we subtract from a char to make it equivalent to the number it represents
    long maxProduct = 0; // stores the maximum product encountered
        // needs to be a long value because of overflow when stored in an integer value
        // I learned this the "long" way...
	std::vector<char> myVector;
	std::fstream myFile;

	myFile.open("grid.txt");

	char i;
	int index = 0;
	while (myFile >> i)
	{
        myVector.resize(index + 1);
        myVector[index] = i;
        index++;

	}
    myFile.close(); // close the file
	for (int i = 0; i < myVector.size() - PRODUCT_WIDTH + 1; i++)
	{
		long product = 1;
        for (int j = 0; j < PRODUCT_WIDTH && myVector[i + j] - CHAR_SUBTRACT >= 0; j++) // in order to test the correctness of the 13 digits
            // ensure that the second part of the condition (after the &&) is commented out
            // or make != a >=
        {
            //to test the correctness of the 13 adjacent digits, print statements were added
            //this prints off a digit one at a time
            //std::cout << myVector[i + j] - CHAR_SUBTRACT;
            product *= (myVector[i + j] - CHAR_SUBTRACT); // multiply product variable by the number at this index
        }
        if (product > maxProduct){
            maxProduct = product; // if the current product is greater than the maximum product, make it the maximum product
        }
        //to test the correctness of the 13 adjacent digits, print statements were added
        //this terminates the line
        //std::cout << std::endl;
	}
    std::cout<< maxProduct << std::endl; // print off the max product
    //print(myVector); // test the vector to see if it is correct
}
