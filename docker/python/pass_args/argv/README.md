# 命令

构建：

    docker build -t pass_args:v1 .

运行容器：

    docker run -it --rm --name pass_args_v1 pass_args:v1

过程：

    $ docker run -it --rm --name pass_args_v1 pass_args:v1
    args: ['main.py']
    Usage: main.py a b
    $ docker run -it --rm --name pass_args_v1 pass_args:v1 3 4
    docker: Error response from daemon: oci runtime error: container_linux.go:247: starting container process caused "exec: \"3\": executable file not found in $PATH".
    $ docker run -it --rm --name pass_args_v1 pass_args:v1 python /hello/main.py 3 4
    args: ['/hello/main.py', '3', '4']
    result: 7
    $ docker run -it --rm --name pass_args_v1 pass_args:v1 python /hello/main.py 3
    args: ['/hello/main.py', '3']
    Usage: main.py a b
    $ docker run -it --rm --name pass_args_v1 pass_args:v1 python /hello/main.py 3 4 5
    args: ['/hello/main.py', '3', '4', '5']
    Usage: main.py a b
    $ docker run -it --rm --name pass_args_v1 pass_args:v1 python /hello/main.py x 4
    args: ['/hello/main.py', 'x', '4']
    Traceback (most recent call last):
      File "/hello/main.py", line 11, in <module>
        a = string.atoi(sys.argv[1])
      File "/usr/local/lib/python2.7/string.py", line 405, in atoi
        return _int(s, base)
    ValueError: invalid literal for int() with base 10: 'x'
    $ 
