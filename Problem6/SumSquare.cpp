#include <stdio.h>
#include <iostream>

// this is the naive approach.
// for a set of numbers between 1 and 100, the naive approach does not take much time at all
int naive()
{
	int hundredSum = 5050; // the sum of all the digits from 1 to 100 (11 * 5)
	int sumSquares = 0;

	for (int i = 1; i <= 100; i++) // iterate through all numbers between 1 and 100
	{
		sumSquares += i * i; // add square of term i
	}
	return hundredSum * hundredSum - sumSquares; // return the answer
}
// I did not algebraically come up with these formulas myself, but the sum formula is famous
// the latter was given to me through the overview
int function()
{
	int limit = 100;
	int hundredSum = (limit * (limit + 1)) / 2; // sum: [n(n+1)]/2
	int sumSquares = (limit * (2 * limit + 1) * (limit + 1)) / 6; // sum of squares: (n+1) * (2n+1) * 1/6 
	return hundredSum * hundredSum - sumSquares; // return the answer
}
// call these two methods and output them to the user
int main()
{
	std::cout << "Naive approach: " << naive() << std::endl;
	std::cout << "Function: " << function() << std::endl;
}