#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>

const int limit = 900000; // the nth number to calculate up to
const int max = 10001; // the nth prime you are trying to find
std::vector<bool> array;
const int limitSqrt = std::sqrt(limit); // square root of one-hundred is ten
int counter = 0;

// sieve of atkin
	// composed of quadratics 	4x^2 + y^2 && n % 12 == 1 or 5
							//	3x^2 + y^2 && n % 12 == 7
							//	3x^2 - y^2 && n % 12 == 11

// my biggest issue with this algorithm was deciding how to filter out non primes
// however I noticed a pattern where 65 was present, which is a multiple of 5
// so I began with that number (5) which happens to be the lower bound in terms of the primes which are
// produced using the sieve of atkin.
// I noticed different implementations continue incrementing the filter up to the square root of the limit, I did the same
// and achieved a perfectly functioning sieve for prime numbers

// a boolean array is useful because it is similar to a map. It represents two values. The first is the number itself, which happens to be the index
// the second is the proposition "n in array[n] is prime"
void atkin()
{
	// this produces all prime candidates
	for (int x = 1; x <= limitSqrt; x++)
	{
		for (int y = 1; y <= limitSqrt; y++)
		{
			// first quadratic, remainder 12 =1 or 5
			int n = (4 * x * x) + (y * y);
			if (n <= limit && (n % 12 == 1 || n % 12 == 5) && !array[n])
			{
				array[n] = true;
				counter++;
			}
			// second quadratic, remainder 12 = 7
			n = (3 * x * x) + (y * y);
			if (n <= limit && (n % 12 == 7) && !array[n])
			{
				array[n] = true;
				counter++;
			}
			// third quadratic, remainder 12 = 11
			n = (3 * x * x) - (y * y);
			if (x > y && n <= limit && (n % 12 == 11) && !array[n])
			{
				array[n] = true;
				counter++;
			}
		}
	}
}

// filters out non primes by finding multiples of x
// used in the quadratic formulas
void filterSquares()
{
	// this removes any non-primes
	for (int i = 5; i <= limitSqrt; i++)
	{
		int s = i;
		for (int k = s; k <= limit; k += s)
		{
			if (k != s && array[k])
			{
				array[k] = false;
				counter--;
			}
		}
	}
}
int main()
{
	/*std::cout << "Enter limit: " << std::endl;
	std::cin >> limit; */
	array.resize(limit); // resize the vector to the nth number to calculate up to
	//fill(): there was a method that would fill the array with false boolean values
		// however the vector constructor does this by default anyways
	// the sieve of atkin only produces primes greater than 3
	array[0] = false;
	array[1] = false;
	array[2] = true;
	array[3] = true;
	counter += 2;
	// that is why we must include 2 and 3 ourselves
	atkin();
	filterSquares();
	std::cout << "Size of vector to calculate primes: " << array.size() << std::endl;
	std::cout << "How many primes encountered: " << counter << std::endl;
	int i = 0;
	for (int primes = 0; i < array.size() && primes < max; i++)
	{
		if (array[i])
		{
			primes++;
		}
	}
	std::cout << "The 10001st prime: " << i - 1 << std::endl; // decrease i by 1 because the final statement within the foor loop
	// increments it by one, including within the last loop
}
