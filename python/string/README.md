# find()

Find a sub string.

If found, return the index of sub string. If not found, return -1.

	>>> s = 'abcd'
	>>> s.find('ab')
	0
	>>> s.find('bc')
	1
	>>> s.find('bcx')
	-1

# index()

If sub string exist, its behaviour is same as find(). But if the sub string does not exist, it will throw an exception of type ValueError.

	>>> s.index('bc')
	1
	>>> s.index('ab')
	0
	>>> s.index('bcx')
	Traceback (most recent call last):
	  File "<stdin>", line 1, in <module>
	ValueError: substring not found
	>>> 
