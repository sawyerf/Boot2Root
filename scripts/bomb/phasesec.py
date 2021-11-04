import os

for i in range(1002):
	fi = open('bite', 'w')
	fi.write('Public speaking is very easy.\n')
	fi.write('1 2 6 24 120 720\n')
	fi.write('0 q 777\n')
	fi.write('9 austinpowers\n')
	fi.write('opekmq\n')
	fi.write('4 2 6 3 1 5\n')
	fi.write(str(i) + '\n')
	fi.close()
	cmd = os.popen('./bomb bite').read()
	if 'BOOM!!!' not in cmd:
			print('win: ' + str(i))
			exit()

