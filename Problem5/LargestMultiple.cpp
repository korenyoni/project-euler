#include <stdio.h>
#include <iostream>
#include <set>
#include <cmath>

// this method uses the sieve of atkin to produce primes
// returns the set of primes which are lower than the value max
std::set<int> primes(int max)
{
	max--; //max needs to be decremented because although the array should contain n + 1
	// (because 0 will also have its own index this way), the limit itself should be n, not n + 1
	int sqrtMax = std::sqrt(max);
	std::set<int> primes;

	primes.insert(2); // we need to add 2
	primes.insert(3); // and 3 manually because the quadratic formulas in the sieve of atkin will
	// only work for producing primes larger or equal to 5.

	// this uses three quadratic formulas to produce primes, and also some other numbers which are multiples
	// of the x and y that you plug into it for x <= sqrtMax
	// and y <= sqrtMax
	for (int x = 1; x <= sqrtMax; x++)
	{
		for (int y = 1; y <= sqrtMax; y++)
		{
			// first quadratic, remainder 12 =1 or 5
			int n = (4 * x * x) + (y * y);
			if (n <= max && (n % 12 == 1 || n % 12 == 5))
			{
				primes.insert(n);
			}
			// second quadratic, remainder 12 = 7
			n = (3 * x * x) + (y * y);
			if (n <= max && (n % 12 == 7))
			{
				primes.insert(n);
			}
			// third quadratic, remainder 12 = 11
			n = (3 * x * x) - (y * y);
			if (x > y && n <= max && (n % 12 == 11))
			{
				primes.insert(n);
			}
		}
	}

	// this removes any non-primes i.e. multiples of x and y 
	for (int i = 5; i <= sqrtMax; i++)
	{
		int s = i;
		for (int k = s; k <= max; k += s)
		{
			if (k != s)
			{
				primes.erase(k);
			}
		}
	}

	return primes;
}
// this method calculates the smallest number that is evenly divisble by all positive integers which are 
// less than or equal to N
int calculateLargestNumber()
{
	int size = 0;
	long answer = 1; // 1 because it will be multiplied
	// prompt the user to enter the number N for which all positive integers under it need to 
	// be factors of the answer
	std::cout << "Enter the number n for which all numbers under\n"
	<< "it need to be a factor of the answer: ";
	std::cin >> size; // size of the array == the amount the user entered
	size++;
	// size plus one because 0 is considered a factor
	int numbers[size]; // declare the array which represents the power of the primes when representing final answer
	// as a unique factor of primes
	for (int i = 0; i < size; i++) // fill the array with 0's
	{
		numbers[i] = 0;
	}

	// this sets the initial powers of all the primes to one
	std::set<int> results = primes(size);
	std::set<int>::iterator it = results.begin(); // the iterator for the set of primes
	for (; it != results.end(); ++it)
	{
		numbers[*it] = 1;
	}

	for (int i = size - 1; i > 1; i--) // i = size - 1 because 0 is included at its own index
		// at the beginning of the array
		// iterate down from N (the number the user entered) to one
	{
		for (int n = 1; n < size; n++) // go through the number array
			// each number is represtented by its index
			// start after 0
		{
			int number = i;
			int power = 0; // how many powers for each prime number do we need to represent a number
			while (numbers[n] > 0 && number % n == 0) // while the number is indeed prime (its initial frequency != 0)
				// and the number is divisible by that prime
			{
				power++; // increment how many powers of that prime we need
				number /= n; // divide the number by the prime
			}
			if (power > numbers[n])
			{
				numbers[n] = power; // if the power exceeds the current power, set
				// the array's value (i.e. its power) at that index to the power variable
			}

		}
	}

	// simply print each element in the array
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "\t----->\t" << numbers[i] << std::endl; // print off the powers for each number
		// for the answer, which is the product of primes
		for (int n = 0; n < numbers[i]; n++)
		{
			answer *= i; // give the answer
		}
	}

	return answer;
}
int main()
{
	std::cout << "answer: " << calculateLargestNumber() << std::endl;
}