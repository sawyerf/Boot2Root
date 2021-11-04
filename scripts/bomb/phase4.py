def func4(arg):
	if arg <= 1:
		return 1
	else:
		return func4(arg - 2) + func4(arg - 1)

for i in range(100):
	ret = func4(i)
	if ret == 55:
		print("yes c'est `{}`".format(i))
		break
	print("{} : {}".format(i, ret))
