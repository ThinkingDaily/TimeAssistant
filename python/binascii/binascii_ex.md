a-flying-bird@flyingbird:~/examples/python$ dd if=/dev/random of=test.dat bs=5 count=2
记录了2+0 的读入
记录了2+0 的写出
10 bytes copied, 9.6496e-05 s, 104 kB/s
a-flying-bird@flyingbird:~/examples/python$ hexdump -C test.dat
00000000  48 ad 45 ec 34 14 48 20  1d e2                    |H.E.4.H ..|
0000000a
a-flying-bird@flyingbird:~/examples/python$ python
Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import binascii
>>> f=open("test.dat", "rb")
>>> bin = f.read()
>>> f.close()
>>> bin
'H\xadE\xec4\x14H \x1d\xe2'
>>> hex = binascii.b2a_hex(bin)
>>> hex
'48ad45ec341448201de2'
>>> 
