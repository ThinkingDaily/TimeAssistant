
#!/usr/bin/env python

import types
import string
import sys

# Transform string or int value to boolean.
def bool(a):
	if type(a) == types.StringType:
		tmp = a.lower()
		if tmp == 'false':
			return False 
		if tmp == 'true':
			return True 
		raise ValueError, "Invalid bool value."

	if type(a) == types.IntType:
	    if a == 0:
	        return False
	    if a == 1:
	        return True
	    raise ValueError, "Invalid bool value."

	if type(a) == types.BooleanType:
		return a 

	raise ValueError, "Invalid bool value."

def helper(value):
	print value, type(value),
	try:
		print bool(value)
	except Exception as e:
		print e 

def foolish(value):
	print 'Foolish!', value, type(value),
	if value:
		print "True"
	else:
		print "False"

if __name__ == "__main__":
	foolish('False')
	foolish('True')

	values = [None, True, False, 0, 1, 'True', 'false', 2, 't', (3, 1)]
	for value in values:
		helper(value)

	if len(sys.argv) == 2:
		helper(sys.argv[1])
