# Command

计算一个文件的md5摘要，以下两个命令都可以。对于第二个命令，dgst的缺省算法是md5.

The following commands can be used to calculate the MD5 of a specified file. For the second command, MD5 is the default digest algorithm.

	openssl md5 filename
	openssl dgst filename

# Example

	$ echo -n Hello, world! > hello.txt

	$ openssl dgst hello.txt
	MD5(hello.txt)= 6cd3556deb0da54bca060b4c39479839

	$ openssl md5 hello.txt
	MD5(hello.txt)= 6cd3556deb0da54bca060b4c39479839

	$

# Python

	>>> import hashlib
	>>> f = open("hello.txt", "rb")
	>>> s = f.read()
	>>> f.close()
	>>>
	>>> hashlib.md5(s)
	<md5 HASH object @ 0000000003863AF8>
	>>> hashlib.md5(s).hexdigest()
	'6cd3556deb0da54bca060b4c39479839'
	>>>
