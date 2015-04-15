package main;

import bigInt.BigInt;
	// my custom BigInt library (:

public class Main
{
	public static void main(String[] args)
	{
		int n = 100;
		BigInt factorial = new BigInt(n);
			// the BigInt representing n at first
		
		for (n--; n > 0; n--)
			// decrement n so it is already n - 1
		{
			factorial.multiply(new BigInt(n));
			// multiply the product by n (which is n - 1)
		}
		
		int sum = 0; // the sum
		String toString = factorial.toString();
			// the string representation of the BigInt
		
		for (int i = 0; i < toString.length(); i++)
			// loop through each index of the toString, then parse the
			// character at that string and add it to the sum
		{
			sum += Integer.parseInt(toString.substring(i, i + 1));
		}
		
		System.out.println(sum);
		
	}
}
