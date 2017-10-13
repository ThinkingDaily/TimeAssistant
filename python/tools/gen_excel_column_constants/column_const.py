#!/usr/bin/python

import sys
import string

'''
Output:
	const int CONST_COLUMN_A = 1;
	const int CONST_COLUMN_B = 2;
	const int CONST_COLUMN_C = 3;
	const int CONST_COLUMN_D = 4;
	const int CONST_COLUMN_E = 5;
	const int CONST_COLUMN_F = 6;
	const int CONST_COLUMN_G = 7;
	...
'''

def GetChar(n):
	if n == 0:
		return ""

	if n > 26:
		print "Invalid n:", n 
		sys.exit(1)

	ORD_A = ord('A')
	return chr(ORD_A + n - 1)

def GenerateColumnConstants(column_count, start_index):
	for i in range(1, column_count + 1):
		if i == 1:
			first_char = 0
			second_char = 1
		else:
			first_char = (i - 1) / 26
			second_char = (i - 1) % 26 + 1

		print "CONST_COLUMN_%s%s = %d" % (GetChar(first_char), GetChar(second_char), i + start_index - 1)

def Usage(program_name):
	print "%s column_count start_index" % (program_name,)

if __name__ == "__main__":
	argc = len(sys.argv)
	if argc != 3:
		Usage(sys.argv[0])
		sys.exit(1)

	GenerateColumnConstants(string.atoi(sys.argv[1]), string.atoi(sys.argv[2]))