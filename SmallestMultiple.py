import math

numberIndex = int(input("Enter x for [1-x] that the number has to be evenly divisible by: "))

def isPrime(i):
	z = []
	n = 0
	for x in range(2, i):
		isPrime = True
		for y in range(2, x - 1):
			if x % y == 0:
				isPrime = False
		if isPrime: z.append(x)
		else: z.append(0)
	n += 1
	return z

p = isPrime(numberIndex)
print(p)

print("---")

# i is primenumbers
# q is 1-20

net = []
for q in range(0,numberIndex - 2):
	net.append(0)

for q in range(1,numberIndex):
	
	index = 0
	for i in p:
		highestPower = 0
		if i != 0 and q % i == 0:
			if highestPower < int(math.log(q,i)):
				highestPower = int(math.log(q,i))
			net[index] = highestPower
		index += 1

print(net)

smallestMultiple = 1

for x in range(0,numberIndex - 2):
	if p[x] != 0:
		smallestMultiple *= pow(p[x], net[x])

print(smallestMultiple)
