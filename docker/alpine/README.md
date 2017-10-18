Alpine GCC/G++ Environment

# gcc

## Ref

https://hub.docker.com/r/frolvlad/alpine-gcc/

命令：

    docker pull frolvlad/alpine-gcc

Dockerfile:

    FROM alpine:3.6

    RUN apk add --no-cache gcc musl-dev

也可以自己基于alpine创建：

    docker run -i --tty --name alpine_inst alpine:3.6
        apk add --no-cache gcc musl-dev
        exit
    docker commit -a "tester" -m "install gcc" alpine_inst examples/alpine:v1
    docker run -it --rm --tty -v /your/dir:/temp examples/alpine:v1
        / # cd /temp
        /temp # ls
        README.md  main.c     main.cpp
        /temp # gcc main.c
        /temp # ./a.out 
        Hello, C!
        /temp # g++ main.cpp
        /bin/sh: g++: not found
        /temp # exit

# g++

## Ref

https://hub.docker.com/r/frolvlad/alpine-gxx/

命令：

    docker pull frolvlad/alpine-gxx

Dockerfile:

    FROM frolvlad/alpine-gcc

    RUN apk add --no-cache g++

Example:

    docker run -it --rm --tty -v /your/dir:/temp frolvlad/alpine-gxx:latest
        / # cd /temp
        /temp # ls
        README.md  a.out      main.c     main.cpp
        /temp # g++ main.cpp
        /temp # ./a.out 
        Hello, C!
        Hello, C++!
        /temp # 

# cmake & curl & make & bash

参考：https://github.com/thar/cmake-compiler-alpine/blob/master/Dockerfile

命令：

    apk update
    apk add cmake
    apk add curl
    apk add make
    apk add bash
    apk add pcre-dev
    apk add curl-dev
    apk add openssl

或

    apk add cmake curl make bash pcre-dev curl-dev curl-dev

# FAQ

## CMAKE_MAKE_PROGRAM is not set

    CMake Error: CMake was unable to find a build program corresponding to "Unix Makefiles".  CMAKE_MAKE_PROGRAM is not set.  You probably need to select a different build tool.
    CMake Error: CMAKE_C_COMPILER not set, after EnableLanguage
    CMake Error: CMAKE_CXX_COMPILER not set, after EnableLanguage
    -- Configuring incomplete, errors occurred!

原因是没有安装make程序，执行如下命令：

    apk add make

## ./xxx.sh: not found

如果shell脚本指定的是/bin/bash，那么会有这种提示。

    /temp/fas # ./test.sh 
    /bin/sh: ./test.sh: not found

可以改成/bin/sh，或者apk add bash.


## pcre

    xxx.hpp:6:18: fatal error: pcre.h: No such file or directory
     #include <pcre.h>
                      ^
    compilation terminated.

解决办法：

    apk add pcre-dev

## curl-dev

    /usr/lib/gcc/x86_64-alpine-linux-musl/6.3.0/../../../../x86_64-alpine-linux-musl/bin/ld: cannot find -lcurl
    collect2: error: ld returned 1 exit status

解决办法：

    apk add curl-dev

## sh: openssl: not found

    apk add openssl
