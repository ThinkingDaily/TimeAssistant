# Question

False不是False，而是True！？

	def foolish(value):
		print 'Foolish!', value, type(value),
		if value:
			print "True"
		else:
			print "False"
	
	if __name__ == "__main__":
		foolish('False')

打印结果：

	Foolish! False <type 'str'> True

# 原因分析

虽然False不是True，但<font color="blue">字符串'False'</font>，的确是True。

通过命令行传参，或者shell脚本调用Python时，有时会习惯地传True或False。这种情况下，Python收到的其实是字符串形式的True和False，由此造成了上述错误。

# bool()小函数

下面的bool()小函数用于避免这种低级错误，将字符串的'True', 'False', 整数的0, 1转换成真正的Boolean type。

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
	
# 运行结果

	$ ./test.py True
	Foolish! False <type 'str'> True
	Foolish! True <type 'str'> True
	None <type 'NoneType'> Invalid bool value.
	True <type 'bool'> True
	False <type 'bool'> False
	0 <type 'int'> False
	1 <type 'int'> True
	True <type 'str'> True
	false <type 'str'> False
	2 <type 'int'> Invalid bool value.
	t <type 'str'> Invalid bool value.
	(3, 1) <type 'tuple'> Invalid bool value.
	True <type 'str'> True
