##Problem 22
*nameScores* is a simple solution to Problem 22.
It reads in about 5000 first names and calculates the sum of their characters' alphabetical
position. The goal is to sum up their name score, which is the sum of their characters'
alphabetical position * the name's alphabetical order in the list.
This is a simple solution using std::map, a tree-based map which automatically orders the names
based on their alphabetical order.
*nameScores* completes its goal in 0.039s.

*nameScoresNoMap* completes the same goal without using a map. It instead uses std::vector<std::string>,
sorts the names using my implementation of quicksort, and my own comparison method for std::string objects.
*nameScoresNoMap* completes its goal in 0.051s.

The time results were timed with *commandTimer*.
