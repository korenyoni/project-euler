a = 1
b = 0
c = 0
n = 0
LIMIT = 4000000


while True:
	b = a		# 1 0 1 1 2 
	a = c		# 0 1 1 2 3
	c = a + b	# 1 1 2 3 5
	if c >= LIMIT:
		break
	elif c % 2 == 0:
		n += c
print(n)
