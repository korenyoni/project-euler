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
	
	// this algorith involves binary trees and recursion.
	// It was effective for calculating a maximum sum path for a triangle of 15 * 15 terms.
	// However it was ineffective for Problem 67 which involves a 100 * 100 triangle

	// populate the ArrayList by parsing each element (integer)
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

	// given any index, find that index's row
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
	// given any index, find the adjacent left index
	private static int goLeft(int startIndex)
	{
		int divergeIndex = startIndex;
		int skip = findRow(startIndex);
		divergeIndex += skip;
		// first element after diverging from the start

		return divergeIndex;
	}
	// given any index, find the adjacent right index
	private static int goRight(int startIndex)
	{
		int divergeIndex = startIndex;
		int skip = findRow(startIndex) + 1;
		divergeIndex += skip;
		// first element after diverging from the start

		return divergeIndex;
	}

	// populate the alternate vector, which only contains elements 
	// minValue or greater
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

	// static inner class for the node of the binary tree
	static class TreeNode {
		int item; // the index of the element in the alternate (myCopy) vector
		TreeNode left; // pointer to left node
		TreeNode right; // pointer to right node

		TreeNode(int item, int rowsLeft, int sum)
		{
			sum += myCopy.get(item); // increment the sum recursively
			this.item = item;
			//results.add(e)
			if (rowsLeft == 1) // if there are no more rows left
			{
				resultNumber++; // increment how many different paths exist
				System.out.println("BANG! " + sum +
						String.format("(%d)", resultNumber)); // print sum
				done = true; // stop the loop in the main method that 
				// calls reduceCopy()
				results.add(sum); // add the sum to the results vector
			}
			else
			{
				int leftElement = myCopy.get(goLeft(item)); // value of adjacent left element
				int rightElement = myCopy.get(goRight(item)); // adjacent right element

				if (leftElement != 0) // if it is not 0 i.e. not less that minValue in reduceCopy()
				{
					left = new TreeNode(goLeft(item), rowsLeft -1, sum); //recursive call to populate left node
				}
				if (rightElement != 0) // if it is not 0 i.e. not less that minValue in reduceCopy()
				{
					right = new TreeNode(goRight(item), rowsLeft -1, sum); //recursive call to populate right node
				}
			}
		}
	}

	private static TreeNode populateNodes(int startIndex)
	{
		TreeNode root = null;
		if (myCopy.get(startIndex) != 0)
		{
			root = new TreeNode(startIndex, maxRows, 0); // call the constructor, this populates all possible nodes for the tree
			// starting with the sum of 0
		}
		return root;
	}

	// taken from HWS
	// this prints the elements in their order from top, left, right
	static void preorderPrint( TreeNode root ) {
		if ( root != null ) {  // (Otherwise, there's nothing to print.)
			System.out.print( myCopy.get(root.item) + " " );  // Print the root item.
			preorderPrint( root.left );   // Print items in left subtree.
			preorderPrint( root.right );  // Print items in right subtree.
		}
	}
	
	// this prints the triangle that corresponds to the alternate vector
	// i.e. it only contains values that are at least minValue from reduceCopy()
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
		populateVector(); // read all the elments in txt file and populate main vector
		System.out.println(myVector);
		TreeNode root = null;
		//System.out.println(myVector.get(goLeft(0)));
		for (int i = 99; i > 0 && !done; i--) // i should iterate down from max element value
		{
			reduceCopy(i); // all elements in alternate vector have to be at least i, otherwise they are 0
			root = populateNodes(0); // populate the binary tree starting from index 0
			System.out.println(i); // print the minValue from reduceCopy()
		}
		preorderPrint(root); // print all elements in order
		System.out.print("\n");
		printEverything(); // print the reduced triangle
		System.out.println(Collections.max(results)); // print the max sum path
	}
}
