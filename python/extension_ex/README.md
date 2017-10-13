g++ -fPIC -std=c++11 -shared mytest.cpp -o add_fns.so

$ g++ -fPIC -std=c++11 -shared mytest.cpp -o add_fns.so
$ ls -l
总用量 20
-rwxrwxr-x 1 ... add_fns.so
-rw-rw-r-- 1 ... mytest.cpp
$ python
Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import add_fns
>>> len, ret = add_fns.add_string("hello", "world")
>>> len
10
>>> ret
'helloworld'
>>> print add_fns.add_int(10, 20)
30
>>> 