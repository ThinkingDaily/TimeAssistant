# Overview

这里配置Filebeat，输出日志到Logstash。

# 配置文件

./myconf/filebeat/filebeat_06.yml

主要部分：

    filebeat.prospectors:
    - type: log
      enabled: true
      paths:
        - /home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/*.log
    output.logstash:
      enabled: true
      hosts: ["localhost:5044"]
    output.console:
      enabled: false
      pretty: true
    path.data: /home/flying-bird/code_snippets/elk/myconf/filebeat/data
    path.logs: /home/flying-bird/code_snippets/elk/myconf/filebeat/logs

需要注意的是，在5.x版本中，可以配置多个output为enabled，但在6.x中行不通，提示：

    $ /.../filebeat test config -e -c /.../filebeat_06.yml
    filebeat2017/11/22 14:43:07.043018 beat.go:625: CRIT Exiting: error unpacking config data: more then one namespace configured accessing 'output' (source:'/.../filebeat_06.yml')
    Exiting: error unpacking config data: more then one namespace configured accessing 'output' (source:'/.../filebeat_06.yml')
    $

# 运行

    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_06.yml

# registry

删除registry，便于表示：

    rm ~/code_snippets/elk/myconf/filebeat/data/registry

# port

在本例中，约定Filebeat和Logstash相互通信的端口号是5044。——当然，双方也可约定其它的端口号。

# prospector.path

需要注意的是，这里的路径不能用相对路径，不能用'~/your_dir/\*.log'，必须把'~'改成绝对路径，否则FileBeat无法捕获日志文件。
