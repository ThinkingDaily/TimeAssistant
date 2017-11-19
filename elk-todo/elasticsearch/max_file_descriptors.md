elasticsearch - max file descriptors

运行时出错：

    [2] bootstrap checks failed
    [1]: max file descriptors [40960] for elasticsearch process is too low, increase to at least [65536]

不能ulimit修改：

    $ ulimit -n
    40960
    $ ulimit -n 65535
    -bash: ulimit: open files: 无法修改 limit 值: 不允许的操作

可以修改配置文件：

    sudo vi /etc/security/limits.conf

改成：

    *   soft    nofile  65535

