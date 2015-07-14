##Problem 21
*firstApproachANF* was the first approach I took to create the amicable number finder.
I did not use any external resources for this one.
In order to calculate the sum of all proper divisors of a number, program runs the number through a recursive method,
findProperDivisorsSum which finds all the proper divisors of a number by recursively dividing the number by all of its
prime factors. It then sums up all the proper divisors.

*fasterApproachANF* was the second approach I took to create the amicable number finder.
Instead of using a recursive method to find all the proper divisors of a number,
I multiplied each prime's sum of itself raised to the power of 0, up to
the power for which it is needed to represent the number. I then subtracted the number
itself from this power since we are considering proper divisors and not all divisors.

After using *commandTimer* for *firstApproachANF* and *fasterApproachANF* for 100 iterations, for the calculation
of all Amicable numbers between 1 and under 10000, the average execution times were:
*0.39385 seconds for firstApproachANF*
*0.24786 seconds for fasterApproachANF*

For all Amicable numbers between 1 and under 100000 with an average calculated with 10 iterations:
*22.5857 seconds for firstApproachANF*
*18.9347 seconds for fasterApproachANF*

For 1000000, each algorithm takes over 2 minutes to calculate.
So the complexity of both algorithms grow quickly.
