# Basic Format

## Encode

	openssl base64 [-e] -in hello.txt // '-e' is optional, it's the default value.
	openssl base64 -in hello.txt > hello.txt.base64 
	openssl base64 -e -in hello.txt -out hello.base64.en

## Decode

	openssl base64 -d -in hello.txt.base64 
	openssl base64 -d -in hello.txt.base64 > hello.txt.base64.de 
	openssl base64 -d -in hello.base64.en -out hello.base64.de

# 注意 Notes

在有些OS下面，需要对入参文件的格式进行调整：每行64个字符，然后加上一个换行符。——文件最后可以有一空行。

On some platform, you should adjust the file format. Each line has 64 characters, with an additional newline.
File can be end with a newline.

# Examples

## Example 1 (>)

	$ echo -n Hello, world! > hello.txt

	$ openssl base64 -in hello.txt
	SGVsbG8sIHdvcmxkIQ==

	$ openssl base64 -in hello.txt > hello.txt.base64

	$ cat hello.txt.base64
	SGVsbG8sIHdvcmxkIQ==

	$ openssl base64 -d -in hello.txt.base64
	Hello, world!
	$ openssl base64 -d -in hello.txt.base64 > hello.txt.base64.de

	$ cat hello.txt.base64.de
	Hello, world!
	$ diff hello.txt hello.txt.base64.de

	$

## Example 2 (-out)

	$ openssl base64 -e -in hello.txt -out hello.base64.en

	$ cat hello.base64.en
	SGVsbG8sIHdvcmxkIQ==

	$ openssl base64 -d -in hello.base64.en -out hello.base64.de

	$ diff hello.txt hello.base64.de

	$

# Python

	>>> import base64
	>>> s = "Hello, world!"
	>>> enc = base64.b64encode(s)
	>>> enc
	'SGVsbG8sIHdvcmxkIQ=='
	>>> t = base64.b64decode(enc)
	>>> t
	'Hello, world!'
	>>>
