# Overview

基于ubuntu image搭建C++、Python开发环境的步骤。

# Base Image

https://hub.docker.com/_/ubuntu/

命令：

    docker pull ubuntu:16.04

过程：

    $ docker pull ubuntu:16.04
    16.04: Pulling from library/ubuntu
    ...
    Status: Downloaded newer image for ubuntu:16.04
    $ docker images
    REPOSITORY  TAG       IMAGE ID      CREATED     SIZE
    ubuntu      16.04     747cb2d60bbe  2 days ago  122 MB
    python      2.7-slim  9724e90f1f17  2 days ago  184 MB
    $

# 安装软件

## g++

命令：

    docker run -it --name ubuntu_instance ubuntu:16.04
    apt-get update
    apt-get --fix-missing install build-essential 
    docker commit -a "email@examples.com" -m "install g++" ubuntu_instance examples/ubuntu:v1

过程：

    $ docker run -it --name ubuntu_instance ubuntu:16.04
    root@425ede3cd51b:/# gcc --version
    bash: gcc: command not found
    root@425ede3cd51b:/# apt-get update
    Get:1 http://security.ubuntu.com/ubuntu xenial-security InRelease [102 kB]
    ...                                    
    Reading package lists... Done
    root@425ede3cd51b:/# apt-get --fix-missing install build-essential 
    Reading package lists... Done
    Building dependency tree       
    Reading state information... Done
    The following additional packages will be installed:
      binutils bzip2 cpp cpp-5 dpkg-dev fakeroot g++ g++-5 gcc gcc-5 ifupdown iproute2 isc-dhcp-client isc-dhcp-common libalgorithm-diff-perl
      libalgorithm-diff-xs-perl libalgorithm-merge-perl libasan2 libatm1 libatomic1 libc-dev-bin libc6-dev libcc1-0 libcilkrts5 libdns-export162 libdpkg-perl
      libfakeroot libfile-fcntllock-perl libgcc-5-dev libgdbm3 libgmp10 libgomp1 libisc-export160 libisl15 libitm1 liblsan0 libmnl0 libmpc3 libmpfr4 libmpx0
      libperl5.22 libquadmath0 libstdc++-5-dev libtsan0 libubsan0 libxtables11 linux-libc-dev make manpages manpages-dev netbase patch perl perl-modules-5.22
      rename xz-utils
    ...
    root@425ede3cd51b:/# exit
    exit
    $ docker ps -a
    CONTAINER ID IMAGE        COMMAND     CREATED      STATUS                   PORTS NAMES
    425ede3cd51b ubuntu:16.04 "/bin/bash" 14 hours ago Exited (0) 3 seconds ago       ubuntu_instance
    $ docker commit -a "email@examples.com" -m "install g++" ubuntu_instance examples/ubuntu:v1
    sha256:6393bfe083ce8cf359907142d2ce01735a85741e3b9140d1dc9ee0170b6fa329
    $ ls


验证：

    $ docker run -it --rm --tty -v /your/host/dir:/temp 6393bfe083ce8cf359907142d2ce01735a85741e3b9140d1dc9ee0170b6fa329
    root@a2311cb2ad24:/# ls
    bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  temp  tmp  usr  var
    root@a2311cb2ad24:/# cd temp
    root@a2311cb2ad24:/temp# ls
    README.md  main.c  main.cpp
    root@a2311cb2ad24:/temp# gcc main.c
    root@a2311cb2ad24:/temp# ./a.out 
    Hello, Docker!
    root@a2311cb2ad24:/temp# rm a.out 
    root@a2311cb2ad24:/temp# g++ main.cpp 
    root@a2311cb2ad24:/temp# ./a.out 
    Hello, Docker!
    root@a2311cb2ad24:/temp# exit
    exit
    $ 

删除临时容器：

    $ docker ps -a
    CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                      PORTS               NAMES
    425ede3cd51b        ubuntu:16.04        "/bin/bash"         14 hours ago        Exited (0) 25 minutes ago                       ubuntu_instance
    $ docker rm 425ede3cd51b
    425ede3cd51b
    $ 

## cmake

主要命令：

    docker run -it --name ubuntu_instance examples/ubuntu:v1
    apt-get --fix-missing install -y cmake
    docker commit -a "email@examples.com" -m "install cmake" ubuntu_instance examples/ubuntu:v2

过程：

    $ docker images
    REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
    examples/ubuntu     v1                  6393bfe083ce        14 hours ago        344 MB
    ubuntu              16.04               747cb2d60bbe        2 days ago          122 MB
    python              2.7-slim            9724e90f1f17        3 days ago          184 MB
    $ docker run -it --name ubuntu_instance examples/ubuntu:v1
    root@37f229bbc08c:/# cmake                                 
    bash: cmake: command not found
    root@37f229bbc08c:/# apt-get --fix-missing install -y cmake
    Reading package lists... Done
    Building dependency tree       
    Reading state information... Done
    The following additional packages will be installed:
      ca-certificates cmake-data krb5-locales libarchive13 libasn1-8-heimdal libcurl3 libexpat1 libffi6 libgnutls30 libgssapi-krb5-2 libgssapi3-heimdal
      libhcrypto4-heimdal libheimbase1-heimdal libheimntlm0-heimdal libhogweed4 libhx509-5-heimdal libicu55 libidn11 libjsoncpp1 libk5crypto3 libkeyutils1
      libkrb5-26-heimdal libkrb5-3 libkrb5support0 libldap-2.4-2 liblzo2-2 libnettle6 libp11-kit0 libroken18-heimdal librtmp1 libsasl2-2 libsasl2-modules
      libsasl2-modules-db libsqlite3-0 libssl1.0.0 libtasn1-6 libwind0-heimdal libxml2 openssl sgml-base xml-core
    ...
    root@37f229bbc08c:/# exit
    exit
    $ docker ps -a
    CONTAINER ID  IMAGE               COMMAND      CREATED  STATUS  PORTS  NAMES
    37f229bbc08c  examples/ubuntu:v1  "/bin/bash"  ...      ...            ubuntu_instance
    $ docker commit -a "email@examples.com" -m "install cmake" ubuntu_instance examples/ubuntu:v2
    sha256:af63c654b51f89d92a85912cffabcd63212093f644d7c2077180d78b88178bcb
    $ docker images
    REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
    examples/ubuntu     v2                  af63c654b51f        13 hours ago        413 MB
    examples/ubuntu     v1                  6393bfe083ce        14 hours ago        344 MB
    ubuntu              16.04               747cb2d60bbe        2 days ago          122 MB
    python              2.7-slim            9724e90f1f17        3 days ago          184 MB
    $ 

删除临时容器：

    $ docker rm 37f229bbc08c
    37f229bbc08c
    $ 

## boost

为了防止下载异常，这里从源码开始安装。

创建容器：

    docker run -it -v /your/host/dir:/temp --name ubuntu_instance examples/ubuntu:v2

安装软件：

    cd /temp
    tar -xvzf boost_1_61_0.tar.gz 
    cd boost_1_61_0
    ./bootstrap.sh --with-libraries=all
    ./b2 install
    cd ..
    rm -rf boost_1_61_0
    g++ boost_test.cpp -o boost_test
    ./boost_test 
    g++ boost_test_regex.cpp -o boost_test_regex -lboost_regex
    ./boost_test_regex < jayne.txt

创建image：

    docker commit -a "email@examples.com" -m "install boost" ubuntu_instance examples/ubuntu:v3
    docker rm <container>

详细命令：

    $ docker images
    REPOSITORY       TAG       IMAGE ID      CREATED             SIZE
    examples/ubuntu  v2        af63c654b51f  14 hours ago        413 MB
    examples/ubuntu  v1        6393bfe083ce  15 hours ago        344 MB
    ubuntu           16.04     747cb2d60bbe  2 days ago          122 MB
    python           2.7-slim  9724e90f1f17  3 days ago          184 MB
    $ docker ps -a
    CONTAINER ID  IMAGE               COMMAND     CREATED  STATUS    PORTS  NAMES
    dabde20842e3  examples/ubuntu:v2  "/bin/bash" ...      Exited...        ubuntu_instance
    $ docker commit -a "email@examples.com" -m "install boost" ubuntu_instance examples/ubuntu:v3
    sha256:01cb4fbbd8c0b3b862ef31433f78817cec0373d138efd34e0a15abea2d1a15e4
    $ docker images
    REPOSITORY       TAG       IMAGE ID      CREATED             SIZE
    examples/ubuntu  v3        01cb4fbbd8c0  13 hours ago        574 MB
    examples/ubuntu  v2        af63c654b51f  14 hours ago        413 MB
    examples/ubuntu  v1        6393bfe083ce  15 hours ago        344 MB
    ubuntu           16.04     747cb2d60bbe  2 days ago          122 MB
    python           2.7-slim  9724e90f1f17  3 days ago          184 MB
    $ docker rm dabde20842e3
    dabde20842e3
    $

## python

命令：

    docker run -it -v /your/host/dir:/temp --name ubuntu_instance examples/ubuntu:v3
    apt-get install python2.7
    ln -f -v /usr/bin/python2.7 /usr/bin/python

详细过程：

    $ docker run -it -v /your/host/dir:/temp --name ubuntu_instance examples/ubuntu:v3
    root@3e34fd96251e:/# python --version
    bash: python: command not found
    root@3e34fd96251e:/# apt-get install python2.7
    Reading package lists... Done
    Building dependency tree       
    Reading state information... Done
    The following additional packages will be installed:
      file libmagic1 libpython2.7-minimal libpython2.7-stdlib mime-support python2.7-minimal
    Suggested packages:
      python2.7-doc binfmt-support
    The following NEW packages will be installed:
      file libmagic1 libpython2.7-minimal libpython2.7-stdlib mime-support python2.7 python2.7-minimal
    0 upgraded, 7 newly installed, 0 to remove and 0 not upgraded.
    ...
    root@3e34fd96251e:/# python
    bash: python: command not found
    root@3e34fd96251e:/# python2.7
    Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
    [GCC 5.4.0 20160609] on linux2
    Type "help", "copyright", "credits" or "license" for more information.
    >>> 3+2
    5
    >>> import json
    >>> a = {"Name": "Tom", "Age":10}
    >>> json.dumps(a)
    '{"Age": 10, "Name": "Tom"}'
    >>> exit()
    root@3e34fd96251e:/# type python2.7
    python2.7 is hashed (/usr/bin/python2.7)
    root@3e34fd96251e:/# ln -f -v /usr/bin/python2.7 /usr/bin/python
    '/usr/bin/python' => '/usr/bin/python2.7'
    root@3e34fd96251e:/# python
    Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
    [GCC 5.4.0 20160609] on linux2
    Type "help", "copyright", "credits" or "license" for more information.
    >>> exit()
    root@3e34fd96251e:/# exit
    exit
    $ 

构建image：

    docker commit -a "email@examples.com" -m "install python 2.7" ubuntu_instance examples/ubuntu:v4
    docker rm <container>

过程：

    $ docker ps -a
    CONTAINER ID  IMAGE               COMMAND     CREATED  STATUS  PORTS  NAMES
    3e34fd96251e  examples/ubuntu:v3  "/bin/bash" ...      ...            ubuntu_instance
    $ docker commit -a "email@examples.com" -m "install python 2.7" ubuntu_instance examples/ubuntu:v4
    sha256:bf842d96952af1474ff8d5e2b8527593301fbf04d9a1282fac0d504d7c364195
    $ docker rm 3e34fd96251e
    3e34fd96251e
    $ 

验证：
    $ docker run -it --rm bf842d96952af
    root@c2bee6dadef6:/# python
    Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
    [GCC 5.4.0 20160609] on linux2
    Type "help", "copyright", "credits" or "license" for more information.
    >>> exit()
    root@c2bee6dadef6:/# 

# 其他软件

## paho-mqtt

   tar zxvf paho-mqtt-1.1.tar.gz
   cd paho-mqtt-1.1
   python setup.py install
   cd ..
   rm -rf paho-mqtt-1.1

## curl

    docker run -it --name ubuntu_instance examples/ubuntu:v5
        apt-get install curl
        apt-get install libcurl4-openssl-dev
    docker commit -a "email@examples.com" -m "install curl" ubuntu_instance examples/ubuntu:v6
    docker rm <container>

## pycurl

    docker run -it -v /your/host/dir:/temp --name ubuntu_instance examples/ubuntu:v6
        apt-get install python-dev
        apt-get install libghc-gnutls-dev
        tar zxvf pycurl-7.43.0.tar.gz
        cd pycurl-7.43.0
        python setup.py install
        cd ..
        rm -rf pycurl-7.43.0
    docker commit -a "email@examples.com" -m "install pycurl" ubuntu_instance examples/ubuntu:v7
    docker rm <container>

## protobuf

    docker run -it -v /your/host/dir:/temp --name ubuntu_instance examples/ubuntu:v7
        apt-get install zip unzip
        unzip protobuf-python-3.4.1.zip

        echo "Building C++ codes..."
        cd protobuf-3.4.1/
        ./autogen.sh
        ./configure
        make
        #make check
        make install

        # protoc: error while loading shared libraries: libprotobuf.so.14: 
        # cannot open shared object file: No such file or directory
        ldconfig


        echo "Building python library..."
        cd python/
        python setup.py build
        python setup.py install
        python setup.py test
        cd ..

        echo "Remove source codes..."
        cd ..
        rm -rf protobuf-3.4.1

# Note

网络环境不好的时候，不要通过Dockerfile一次性安装多个软件，因为其中一个出错就会导致整个image创建失败。

可以通过容器方式构建image，且增量式创建image。

每个image创建完之后，都再创建对应的容器进行验证。

