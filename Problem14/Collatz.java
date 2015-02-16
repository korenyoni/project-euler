<<<<<<< HEAD
package collatz;

public class Collatz
{
	private static final int MAX = 999999;
	private static int[] collatzLengthArray = new int[MAX];
	public static void main(String[] args)
	{
		populateArray();
		int maxLength = 0;
		int currentMax = 0;
		int maxNumber = 0;
		for (int number = 900000; number < MAX; number++)
		{
			currentMax = getCollatzLength(number);
			if (currentMax > maxLength)
			{
				maxLength = currentMax;
				maxNumber = number;
			}
		}
		System.out.printf("Maximum length for numbers under %d: %d (%d)\n", MAX, maxLength, maxNumber);
	}
	public static void populateArray()
	{
		for (int i = 0; i < collatzLengthArray.length; i++)
		{
			collatzLengthArray[i] = -1;
		}
	}
	public static int getCollatzLength(int number)
	{
		int length = 1;
		int precalcLength = 0;
		int originalNumber = number;
		while (number > 1)
		{
			if (number <= collatzLengthArray.length - 1)
			{
				precalcLength  = collatzLengthArray[number -1];
				if (precalcLength != -1)
				{
					length += precalcLength -1;
					System.out.printf("Hit precalcLength for number %d: %d\n", number, precalcLength);
					collatzLengthArray[originalNumber - 1] = length;
					return length;
				}
			}
			else
			{
				if (number % 2 == 0)
				{
					number /= 2;
				}
				else
				{
					number = (3 * number) + 1;
				}
				length++;
			}
		}
		collatzLengthArray[originalNumber - 1] = length;
		return length;
	}
}
=======
package collatz;

public class Collatz
{
	private static final int MAX = 999999;
	private static int[] collatzLengthArray = new int[MAX];
	public static void main(String[] args)
	{
		populateArray();
		int maxLength = 0;
		int currentMax = 0;
		int maxNumber = 0;
		for (int number = 900000; number < MAX; number++)
		{
			currentMax = getCollatzLength(number);
			if (currentMax > maxLength)
			{
				maxLength = currentMax;
				maxNumber = number;
			}
		}
		System.out.printf("Maximum length for numbers under %d: %d (%d)\n", MAX, maxLength, maxNumber);
	}
	public static void populateArray()
	{
		for (int i = 0; i < collatzLengthArray.length; i++)
		{
			collatzLengthArray[i] = -1;
		}
	}
	public static int getCollatzLength(int number)
	{
		int length = 1;
		int precalcLength = 0;
		int originalNumber = number;
		while (number > 1)
		{
			if (number <= collatzLengthArray.length - 1)
			{
				precalcLength  = collatzLengthArray[number -1];
				if (precalcLength != -1)
				{
					length += precalcLength -1;
					System.out.printf("Hit precalcLength for number %d: %d\n", number, precalcLength);
					collatzLengthArray[originalNumber - 1] = length;
					return length;
				}
			}
			else
			{
				if (number % 2 == 0)
				{
					number /= 2;
				}
				else
				{
					number = (3 * number) + 1;
				}
				length++;
			}
		}
		collatzLengthArray[originalNumber - 1] = length;
		return length;
	}
}
>>>>>>> Added problem 14
