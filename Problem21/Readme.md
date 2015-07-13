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

firstApproachANF calculates the sum of all amicable numbers staring from 1 and under 10000 very quickly.
for 100000 as the limit, it takes 21 seconds.
fasterApproachANF calculates all the amicable numbers under 10000 very quickly and for
100000, it takes 19 seconds, which is not much of a difference.

for 1000000, each algorithm takes over 2 minutes to calculate.
