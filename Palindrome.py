highestNumber = 0

def reverse(number):
	rev = 0
	num = number
	assert num >= 0
	while num > 0:
		rev = rev * 10 + num % 10
		num = int(num / 10)
	return rev

for x in range(1000,99,-1):
	for n in range(1000,99,-1):
		number = x * n
		if reverse(number) == number:
			if number > highestNumber:
				highestNumber = number
print(highestNumber)
