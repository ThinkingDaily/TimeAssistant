# Overview

读写本地文件。

增加读文件的功能：读取json文件，再把结果写到另外一个txt文件。

    /app/conf/test.json
    /app/logs/test.log

# 构建image

    docker build -t hellopython_v3 .

# 运行

将本地目录和容器用到的目录对应起来，运行可以发现host自动会创建这个目录，且容器把数据写到host对应的文件上。

    docker run -v ~/examples/docker/test_v3:/app hellopython_v3

需要本地的这个目录上创建有conf和logs目录。

