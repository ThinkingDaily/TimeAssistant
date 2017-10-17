# Ref

See: https://docs.python.org/2.7/library/getopt.html

# Example

	$ ./test.py -a 1234 -b -c -d hello test.txt
	option a: 1234
	option b
	option c
	option d: hello
	args: ['test.txt']
	$ ./test.py -a1234 -b -dhello test.txt
	option a: 1234
	option b
	option d: hello
	args: ['test.txt']
	$ ./test.py -a1234 -b --dhello test.txt
	usage:...
	** option --dhello not recognized **
	$ ./test.py -a1234 -b -dhello --bar test.txt
	usage:...
	** option --bar not recognized **
	$ 
