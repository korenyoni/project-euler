package triangleSum;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.TreeSet;
import java.io.File;
import java.io.FileNotFoundException;

public class TriangleSum
{

	private static ArrayList<Integer> myVector = new ArrayList<Integer>();
	private static ArrayList<Integer> myCopy = new ArrayList<Integer>();
	private static ArrayList<Integer> results = new ArrayList<Integer>();
	private static int size;
	private static int maxRows = 0;
	private static int resultNumber = 0;
	private static boolean done = false;
	private static String path =
			"/home/kavkaz/workspace/TriangleSumJava/src/triangleSum/triangle.txt";

	private static void populateVector() throws FileNotFoundException
	{
		Scanner input = new Scanner(new File(path));
		while (input.hasNextInt())
		{
			myVector.add(input.nextInt());
		}

		size = myVector.size();
		input.close();
		maxRows = findRow(size - 1);
		System.out.println(maxRows + " <--- maximum rows");
	}

	private static int findRow(int index)
	{
		//finds the row
		int i = 1;
		int n = 1;
		while(index + 1 >= i)
		{
			i += n;
			n++;
		}
		return n - 1;
	}
	private static int goLeft(int startIndex)
	{
		int divergeIndex = startIndex;
		int skip = findRow(startIndex);
		divergeIndex += skip;
		// first element after diverging from the start

		return divergeIndex;
	}
	private static int goRight(int startIndex)
	{
		int divergeIndex = startIndex;
		int skip = findRow(startIndex) + 1;
		divergeIndex += skip;
		// first element after diverging from the start

		return divergeIndex;
	}

	private static void reduceCopy(int minValue)
	{
		myCopy.clear();
		for (int i = 0; i < size; i++)
		{
			myCopy.add(0);
		}
		for (int i = 0; i < size; i++)
		{
			int term = myVector.get(i);
			if(term >= minValue)
			{
				myCopy.set(i, term);
			}
		}
	}

	static class TreeNode {
		int item;
		TreeNode left;
		TreeNode right;

		TreeNode(int item, int rowsLeft, int sum)
		{
			sum += myCopy.get(item);
			this.item = item;
			//results.add(e)
			if (rowsLeft == 1)
			{
				resultNumber++;
				System.out.println("BANG! " + sum +
						String.format("(%d)", resultNumber));
				done = true;
				results.add(sum);
			}
			else
			{
				int leftElement = myCopy.get(goLeft(item));
				int rightElement = myCopy.get(goRight(item));

				if (leftElement != 0)
				{
					left = new TreeNode(goLeft(item), rowsLeft -1, sum);
				}
				if (rightElement != 0)
				{
					right = new TreeNode(goRight(item), rowsLeft -1, sum);
				}
			}
		}
	}

	private static TreeNode populateNodes(int startIndex)
	{
		TreeNode root = null;
		if (myCopy.get(startIndex) != 0)
		{
			root = new TreeNode(startIndex, maxRows, 0);
		}
		return root;
	}

	// taken from HWS
	static void preorderPrint( TreeNode root ) {
		if ( root != null ) {  // (Otherwise, there's nothing to print.)
			System.out.print( myCopy.get(root.item) + " " );  // Print the root item.
			preorderPrint( root.left );   // Print items in left subtree.
			preorderPrint( root.right );  // Print items in right subtree.
		}
	}
	
	private static void printEverything()
	{
		for (int x = 0; x < size; x++)
		{
			int term = myCopy.get(x);
			if (term == 0)
			{
				System.out.printf("__ ");
			}
			else
			{
				System.out.printf("%02d ", term);
			}
			if (findRow(x) < findRow(x + 1))
			{
				System.out.print("\n");
			}
		}

	}

	public static void main(String[] args) throws FileNotFoundException
	{
		populateVector();
		System.out.println(myVector);
		TreeNode root = null;
		//System.out.println(myVector.get(goLeft(0)));
		for (int i = 99; i > 0 && !done; i--) // i should iterate down from max element value
		{
			reduceCopy(i);
			root = populateNodes(0);
			System.out.println(i);
		}
		preorderPrint(root);
		System.out.print("\n");
		printEverything();
		System.out.println(Collections.max(results));
	}
}
