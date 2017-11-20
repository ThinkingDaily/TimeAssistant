Filebeat运行时，会把日志处理的当前进展记录在data/registry文件中。下次运行Filebeat时，会根据registry中的信息，处理新产生的日志内容。

registry文件的示例：

    flying-bird@flyingbird:~$ cat ~/code_snippets/elk/myconf/filebeat/data/registry 
    [
    {
        "source":"/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/test.log",
        "offset":23,
        "timestamp":"2017-11-20T21:46:57.144354027+08:00",
        "ttl":-1,
        "type":"log",
        "FileStateOS":{
            "inode":5782373,
            "device":2053
        }
    }
    ]
    flying-bird@flyingbird:~$ 

在调试阶段，通常使用同一个日志文件，且都需要从头开始处理该日志文件。为此，可以在每次运行Filebeat之前，删除registry文件。

    rm ~/code_snippets/elk/myconf/filebeat/data/registry

