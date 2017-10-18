# Overview

增加写文件的功能，文件名：

    fn = "/app/test.txt"

# 构建

    docker build -t hellopython_v2 .

# 运行

    将本地目录和容器用到的目录对应起来，运行可以发现host自动会创建这个目录，且容器把数据写到host对应的文件上。

    docker run -v ~/examples/docker/ttt:/app hellopython_v2

# Detail

    $ docker run -v ~/examples/docker/ttt:/app hellopython_v2
    Hello, Python!
    $ ls ..
    busybox.tar dockerfile.md   py_hello    registry.md test_py
    data        mydockerbuild   py_hello_v2 repo.md     ttt
    $ ls ../ttt/
    test.txt
    $ ls ../ttt/test.txt 
    ../ttt/test.txt
    $ cat ../ttt/test.txt 
    Hello, Python!$

如果不映射到host，且容器中没有创建/app目录，那么运行会报错：

    $ docker run hellopython_v2
    Traceback (most recent call last):
      File "main.py", line 13, in <module>
        foo()
      File "main.py", line 10, in foo
        Hello, Python!
    write_file(fn, "Hello, Python!")
      File "main.py", line 3, in write_file
        f = open(filename, "wb")
    IOError: [Errno 2] No such file or directory: '/app/test.txt'
    $ 
