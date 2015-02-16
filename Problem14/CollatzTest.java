<<<<<<< HEAD
package collatz;

public class CollatzTest
{
	public static void main(String[] args)
	{
		int arrayElements = 50;
		int[][] testArray = new int[1][50];
		int arrayIndex = 0;
		
		for (int i = 0; i < 1000 ; i += 1)
		{
			if (i < arrayElements * (arrayIndex -1))
			{
				testArray[arrayIndex][i] = i;
			}
			else if (i > arrayElements) // 105 % 50 = 5 | 100 / arrayElements = 2
			{
				arrayIndex = (i - (i % arrayElements)) / arrayElements;
				int[][] copy = new int[arrayIndex + 1][arrayElements];
				for(int b = 0; b < testArray[arrayIndex -1].length; b++)
				{
					copy[arrayIndex -1][b] = testArray[arrayIndex -1][b];
				}
				testArray = copy;
			}
		}
		System.out.println(testArray.length);
		for (int[] i : testArray)
		{
			System.out.println(i[1]);
		}
	}
}
=======
package collatz;

public class CollatzTest
{
	public static void main(String[] args)
	{
		int arrayElements = 50;
		int[][] testArray = new int[1][50];
		int arrayIndex = 0;
		
		for (int i = 0; i < 1000 ; i += 1)
		{
			if (i < arrayElements * (arrayIndex -1))
			{
				testArray[arrayIndex][i] = i;
			}
			else if (i > arrayElements) // 105 % 50 = 5 | 100 / arrayElements = 2
			{
				arrayIndex = (i - (i % arrayElements)) / arrayElements;
				int[][] copy = new int[arrayIndex + 1][arrayElements];
				for(int b = 0; b < testArray[arrayIndex -1].length; b++)
				{
					copy[arrayIndex -1][b] = testArray[arrayIndex -1][b];
				}
				testArray = copy;
			}
		}
		System.out.println(testArray.length);
		for (int[] i : testArray)
		{
			System.out.println(i[1]);
		}
	}
}
>>>>>>> Added problem 14
