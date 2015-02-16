package collatz;

import java.util.HashMap;

public class Collatz2
{
	private static HashMap<Long, Integer> map = new HashMap<Long, Integer>();
	public static final int MAX = 1000000;
	
	public static void main(String[] args)
	{
		int maxLength = 0;
		long maxNumber = 1;
		for (long i = 1; i < MAX; i++)
		{
			int currentLength = getCollatzLength(i);
			if (currentLength > maxLength)
			{
				maxNumber = i;
				maxLength = currentLength;
			}
		}
		System.out.printf("The biggest chain is %d and belongs to\nthe number %d", maxLength, maxNumber);
	}
	public static int getCollatzLength(long number)
	{
		long numberCopy = number;
		int collatzLength = 1;
		if (map.containsKey(number))
		{
			int value = collatzLength + map.get(number) - 1;
			map.put(numberCopy, value);
			return value;
		}
		while (number > 1)
		{
			//System.out.println(number);
			if (number % 2 == 0)
			{
				number /= 2;
			}
			else
			{
				number = (number * 3) + 1;
			}
			collatzLength++;
		}
		map.put(numberCopy, collatzLength);
		return collatzLength;
	}
}
