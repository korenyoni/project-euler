#include <stdio.h>
#include <iostream>

// find the reverse of the number
int reverse(int number)
{
	int numberReverse = 0;
	const int i = 10;
	while (number > 0)
	{
		numberReverse *= i; // multiply the reverse number by 10
		numberReverse += number % i; // add the remainder of the number divided by 10
		// that is add the last digit of the number to the result
		number /= i; // truncate the original number by one digit
	}
	return numberReverse;
}
int main()
{
	bool found = false; // the number is found
	int max = 0; // maximum palindrome number
	for (int i = 999; i > 900 && !false; i--) // only need to iterate between 999 down to 900
		// because each set of numbers for i * n where i < 100-199 && n < 100-199, 200-299, 300-399 etc 
		//will produce a palindrome but we are concerned with the largest palindrome produced by two
		//three digit numbers i*n, so i and n are both located between 900 and 999
		// i
	{
		for (int n = 999; n > 900 && !false; n--) // n
		{
			if (reverse(i * n) == i*n && i*n > max)
			{
				max = i * n;
			}
		}
	}
	std::cout << max << std::endl; // output the maximum palindrome produced by two three
	// digit numbers
}