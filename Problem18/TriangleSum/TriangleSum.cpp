#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream myFile;
vector<int> elements;
int arraySize;
int rows = 1;

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
int goLeft(int startIndex)
{
	int divergeIndex = startIndex;
	int skip = findRow(startIndex);
	divergeIndex += skip;
	// first element after diverging from the start

	return divergeIndex;
}
int goRight(int startIndex)
{
	int divergeIndex = startIndex;
	int skip = findRow(startIndex) + 1;
	divergeIndex += skip;
	// first element after diverging from the start
	
	return divergeIndex;
}
int findMaximumSum()
{
	// to go down the left side of the triangle, we start at the first element
	// and skip 0 elements, then 1, then 2, then 3 etc.
	// to go right, we start at the first element and skip 1 element, 2, 3, etc.

	int startIndex = 0;
	int leftSum = 0;
	int rightSum = 0;
	int index = 0;
	int sum = 0;

	for (int x = 0; x < rows; x++)
	{
		cout << elements[startIndex] << endl;
		sum += elements[startIndex];
		rightSum = 0;
		leftSum = 0;
		index = startIndex;
		// right sum
		for (int n = 1; n < rows - x; n++)
		{
			index = goRight(index);
			rightSum += elements[index];
		}
		index = startIndex; // reset the index
		// left sum
		for (int n = 1; n < rows - x; n++)
		{
			index = goLeft(index);
			leftSum += elements[index];
		}
		if (rightSum > leftSum) // go right if rightsum is bigger than leftsum
		{
			cout << "RIGHT! " << rightSum << "> " << leftSum << endl;
			startIndex = goRight(startIndex);
		}
		else // otherwise go left
		{
			cout << "LEFT " << rightSum << "< " << leftSum << endl;
			startIndex = goLeft(startIndex);
		}
	}

	return sum;
}
int main()
{
	arraySize = readNumberElements();
	elements.resize(arraySize);
	populateArray();
	//cout << rows << endl;
	int n = findMaximumSum();
	cout << "Sum: " << n << endl;
	/*for (int x = 0; x < elements.size(); x++)
	{
		cout << elements[x] << endl;
	}*/
	//cout << elements[goLeft(1)] << endl;
}
