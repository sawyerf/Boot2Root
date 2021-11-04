import os

def str_base(val, base=7):
		res = ''
		while val > 0:
				res = ' ' + str(val % base) + res
				val //= base # for getting integer division
		if res:
				return res
		return '0'

for i in range(16806):
		nb = '4' + str_base(i)
		if len(nb) == 11 and '0' not in nb and len("".join(set(nb))) == 7:
				fi = open('bite', 'w')
				fi.write('Public speaking is very easy.\n')
				fi.write('1 2 6 24 120 720\n')
				fi.write('0 q 777\n')
				fi.write('9 austinpowers\n')
				fi.write('opekmq\n')
				fi.write(nb + '\n')
				fi.close()
				cmd = os.popen('./bomb bite; cat bite').read()
				if 'BOOM!!!' not in cmd:
						print('win: ' + nb)
						exit()

