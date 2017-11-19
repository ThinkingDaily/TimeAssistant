Shell - tee

# Key Point

将程序的日志既打印到控制台，也写到日志文件。

    ./test.sh | tee test.log
    ./test.sh | tee -a test.log  // -a: append

# Example

    $ cat test.sh
    #!/bin/bash

    echo "hello, tee.!"

    $ cat test.py
    #!/usr/bin/env python

    print "Hello, tee!"
    $ cat test.c
    #include <stdio.h>

    int main()
    {
        printf("Hello, tee!\n");
        return 0;
    }

    $ chmod +x test.sh
    $ chmod +x test.py
    $ gcc -o testc test.c
    $ ./testc | tee testc.log
    Hello, tee!
    $ ./test.py | tee testpy.log
    Hello, tee!
    $ ./test.sh | tee testsh.log
    hello, tee.!
    $ ./test.sh | tee -a testsh.log
    hello, tee.!
    $ cat testc.log
    Hello, tee!
    $ cat testpy.log 
    Hello, tee!
    $ cat testsh.log
    hello, tee.!
    hello, tee.!
