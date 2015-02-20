// calculates the number of possible paths going from the top left of a grid
// down to the bottom left, being able to only move down and right.
/// Natrually this represents half of all movements, so the solution can be solved in
// combinations. Say you have a 3x3 grid, you will do (3+3)! / [(3+3)-3]!*3!

// When doing very large factorials, there is a need to simplify. You can do this
// Algebraically, and this program makes use of arrays to do so.

#include<iostream>

using namespace std;

// sideLength: e.g. if this is a 3x3 grid, sideLength = 3
long getFactorial(int sideLength)
{
	// these will be the final numerator and denominator of the combination
	// Formula. These variables are initialized to 1 because they will be involved
	// in multiplication
	long finalNumerator = 1;
	long finalDenominator = 1;
	// this represents the numerator factorial
	int numerator = sideLength * 2;
	// this array represents the numerator
	int numeratorArray [sideLength];
	int denominatorArray [sideLength]; // the denominator
	// used in second for-loop:
	int numElement = 0;
	int denElement = 0;
	bool numNotOne = false;
	bool denNotOne = false;

	for (int x = 0; x < sideLength; x++)
	{
		denominatorArray[x] = sideLength - x;
		numeratorArray[x] = numerator - x;
	}

	// the numerator is now simplified
	for (int x = 0; x < sideLength; x++)
	{
		numElement = numeratorArray[x];
		numNotOne = numElement > 1;
		for (int n = 0; n < sideLength; n++)
		{
			denElement = denominatorArray[n];
			denNotOne = denElement > 1;
			if (numNotOne && denNotOne &&
				numElement % denElement == 0 && numElement >= denElement)
			{
				cout << numeratorArray[x] << " / " << denominatorArray[n] <<
				" =  " << numeratorArray[x]/denominatorArray[n] << endl;
				numeratorArray[x] = numElement / denominatorArray[n];
				denominatorArray[n] = 1;
				numElement = numeratorArray[x];
			}
		}
	}

	for (int x = 0; x < sideLength; x++)
	{
		finalNumerator *= (long)numeratorArray[x];
		cout <<"Numerator: " << finalNumerator << endl;
		finalDenominator *= (long)denominatorArray[x];
		cout <<"Denominator: " << finalDenominator << endl;
	}
	return (finalNumerator / finalDenominator);
}
int main()
{
	long answer = getFactorial(20);
	cout << "The number of paths: " << answer << endl;
}
