# Commands

	openssl enc -aes-256-cbc -salt -in hello.txt -out hello.txt.aes
	openssl enc -aes-256-cbc -d -salt -in hello.txt.aes -out hello.txt.out

or

	openssl aes-256-cbc -salt -in hello.txt -out hello.txt.aes
	openssl aes-256-cbc -d -salt -in hello.txt.aes -out hello.txt.out

# Example

	$ openssl enc -aes-256-cbc -salt -in hello.txt -out hello.txt.aes
	enter aes-256-cbc encryption password:
	Verifying - enter aes-256-cbc encryption password:
	$ hexdump -C hello.txt.aes 
	00000000  53 61 6c 74 65 64 5f 5f  f4 1a 90 27 28 32 72 6d  |Salted__...'(2rm|
	00000010  e3 71 9e 99 79 22 15 07  a9 8f f6 a4 00 06 1b 96  |.q..y"..........|
	00000020
	$ openssl enc -aes-256-cbc -d -salt -in hello.txt.aes -out hello.txt.out
	enter aes-256-cbc decryption password:
	$ hexdump -C hello.txt.out 
	00000000  48 65 6c 6c 6f 2c 20 77  6f 72 6c 64 21 0a        |Hello, world!.|
	0000000e
	$ diff hello.txt hello.txt.out
	$ 

# K&IV

	$ echo hello > hello.txt
	$ openssl enc -aes-128-cbc -in hello.txt -out hello.en -K 1234 -iv abcd
	$ ls -l
	total 16
	-rw-r--r--  1 user  group  16  7  4 16:34 hello.en
	-rw-r--r--  1 user  group   6  7  4 16:34 hello.txt
	$ hexdump -C hello.en 
	00000000  06 b5 a2 18 b2 af d9 77  2b d2 12 03 49 0a ea 58  |.......w+...I..X|
	00000010
	$ openssl enc -aes-128-cbc -d -in hello.en -out hello.de -K 1234 -iv abcd
	$ ls -l
	total 24
	-rw-r--r--  1 user  group   6  7  4 16:35 hello.de
	-rw-r--r--  1 user  group  16  7  4 16:34 hello.en
	-rw-r--r--  1 user  group   6  7  4 16:34 hello.txt
	$ cat hello.de 
	hello
	$ 
