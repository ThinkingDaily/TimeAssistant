# Overview

filebeat在后台运行，后续要kill掉该进程的方法。

# Key Points

通过ps找到PID：

    ps -ef |grep "filebeat"

如：

    flying-+  5063  4517  0 22:23 pts/1    00:00:00 /.../filebeat -e -c /.../filebeat_01.yml
    flying-+  5086  4517  0 22:23 pts/1    00:00:00 grep --color=auto filebeat

然后 sudo kill 5063 即可。

# Example

    flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml &
    [1] 5063 <--- 这里显示了当前启动的filebeat的PID
    flying-bird@flyingbird:~$ 
    flying-bird@flyingbird:~$ ps -ef |grep "filebeat"
    flying-+  5063  4517  0 22:23 pts/1    00:00:00 /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml
    flying-+  5086  4517  0 22:23 pts/1    00:00:00 grep --color=auto filebeat
    flying-bird@flyingbird:~$ 
    flying-bird@flyingbird:~$ sudo kill 5063
    [sudo] password for flying-bird: 
    flying-bird@flyingbird:~$ 2017/11/22 14:24:24.169656 filebeat.go:311: INFO Stopping filebeat
    ...
    2017/11/22 14:24:24.231057 beat.go:268: INFO filebeat stopped.
    
    [1]+  Done                    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml
    flying-bird@flyingbird:~$ 
