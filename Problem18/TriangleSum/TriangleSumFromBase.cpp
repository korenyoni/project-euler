#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

ifstream myFile;
vector<int> elements;
int arraySize;
int rows = 1;

// this is a more efficient method of solving the maximum path sum problem.
// I ran into this algorithm after solving a 15*15 right triangle of elements using a binary tree.
// Since you must start from the top, you can only go left and right down. Starting from the bottom row and for each adjacent pair
// of two elements and adding the maximum of the two onto their root, you will find the maximum path sum for a triangle of those three terms.
// If you keep working your way up you will do this for the whole triangle.
int readNumberElements()
{
	myFile.open("triangle.txt");
	int i;
	int count = 0;

	while (myFile >> i)
	{
		count++;
	}

	myFile.close();
	return count;
}
void populateArray()
{
	int elementsPerRow = 1;
	int n = 1;
	myFile.open("triangle.txt");
	int i = 0;
	while (myFile >> elements[i])
	{
		if (i == elementsPerRow)
		{
			n++;
			elementsPerRow += n;
			rows++;
		}
		// count number of rows
		i++;
	}
	myFile.close();

}
int findRow(int index)
{
	//finds the row
	int i = 1;
	int n = 1;
	while(index + 1 >= i)
	{
		i += n;
		n++;
	}
	return n - 1;
}
// returns the maximum of the two arguments
int max(int a, int b)
{
	if (a - b < 0)
	{
		return b;
	}
	return a;
}
// find the first index of the row with that particular number (1 -> n)
int findFirstAtRow(int row)
{
	int n = 0;
	int i = 0;
	for (; n < row; n++)
	{
		i += n;
	}
	return i;
}
// finds the max of the two elements adjacent to the element at the specified index
int findBottomMax(int index)
{
	return max(elements[index + findRow(index)], // go down left
			elements[index + findRow(index) + 1]); // go down right
}
// performs a sum of maximum paths (by adding the maximum of the two adjacent elements onto it)
// for each element in the second last row, working the way up until the first row,
// that is the very first element. This is the maximum path sum of the triangle.
int sumUpwards()
{
	int row = rows - 1; // start at second last row
	int n;
	for (; row > 0; row--) // move upwards, iterate down the rows
	{
		// nested loop which iterates through each element in the row\
		// and calls findBottomMax(int)
		n = findFirstAtRow(row);
		for (int i = n; findRow(i) == row; i++)
		{
			elements[i] += findBottomMax(i); // add the max of the two
			//adjacent elements to the top element
		}
	}
	return elements[0]; // return the topmost element
	// this contains the maximum path sum
}
int main()
{
	arraySize = readNumberElements();
	elements.resize(arraySize);
	populateArray();
	cout << sumUpwards() << endl;
	return 0;
}
