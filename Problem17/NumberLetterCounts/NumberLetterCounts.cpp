#include <stdio.h>
#include <iostream>

using namespace std;

/*
 * one = 3
 * two = 3
 * four = 4
 * five = 4
 * six = 3
 * seven = 5
 * eight = 5
 * nine = 4
 *
 * twenty = 6
 * thirty = 6
 * forty = 5
 * fifty = 5
 * sixty = 5
 * seventy = 7
 * eighty = 6
 * ninety = 6
 *
 * hundred = 7
 * and = 3
 *
 */

int digits[] = {0,3,3,5,4,4,3,5,5,4,0,3,6,6,5,5,5,7,6,6};
int teens[] = {6,6,8,8,7,7,9,8,8};
const int AND = 3;
const int HUNDRED = 7;
const int THOUSAND = 8;

int countLetters(int number)
{
	int sum = 0;
	int tenColumn;
	int singleColumn;
	int hundreds;
	hundreds = number/100; // truncate to number of hundreds (eg 0, 1, 2)
	sum += digits[hundreds];
	if (hundreds > 0)
	{
		sum += HUNDRED; // eg one HUNDRED ...

	}
	// none if less than 100, one-hundred if 1, two-hundred etc.
	tenColumn = number % 100;
	if (tenColumn != 0 && hundreds > 0)
	{
		sum += AND; // one hundred AND ...
	}
	// ... if the number is not exactly a multiple of 100
	if (tenColumn > 10 && tenColumn < 20)
	{
		tenColumn -= 11;
		sum += teens[tenColumn];
	}
	else {
		singleColumn = tenColumn % 10; // take the single column out of a two digit number
		// eg 6 out of 76
		tenColumn /= 10; // truncate the single column out of two digit number and reduce
		// that number to a single digit number
		sum += digits[singleColumn];
		sum += digits[tenColumn + 10];
	}

	return sum;
}
int main()
{
	int sum = 0;
	for (int i = 1; i < 1000; i++)
	{
		sum += countLetters(i);
	}
	sum += digits[1] + THOUSAND;
	cout << sum << endl;

	cout << countLetters(10) << endl;
	// 143
	// one hundred and forty three
	// 3 + 7 + 3 + 5 + 5
	// 23
}
