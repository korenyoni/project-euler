#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream myFile;
vector<int> elements;
vector<int> elementsCopy;
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
	myFile.close();

}
void populateCopy()
{
	elementsCopy.clear();
	elementsCopy.resize(elements.size());
	for (int x = 0; x < elements.size();x++)
	{
		elementsCopy[x] = elements[x];
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
int subLeftTriangle(int startIndex)
{ 
	populateCopy();
	int index = startIndex;
	int sum = 0;
	elementsCopy[startIndex] = 0;
	while (index < elementsCopy.size())
	{
		index = goRight(index);
		elementsCopy[index] = 0;
	}
	for (int x = startIndex; x < elementsCopy.size(); x++)
	{
		sum += elementsCopy[x];
	}
	return sum;
}
int subRightTriangle(int startIndex)
{
	populateCopy();
	int index = startIndex;
	int sum = 0;
	elementsCopy[startIndex] = 0;
	while (index < elementsCopy.size())
	{
		index = goLeft(index);
		elementsCopy[index] = 0;
	}
	for (int x = startIndex; x < elementsCopy.size(); x++)
	{
		sum += elementsCopy[x];
	}
	return sum;
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
		// right sum
		rightSum = subRightTriangle(startIndex);
		leftSum = subLeftTriangle(startIndex);
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
