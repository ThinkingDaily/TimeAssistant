# Ref

- Getting Started With Filebeat: https://www.elastic.co/guide/en/beats/filebeat/current/filebeat-getting-started.html
- 源码: https://github.com/elasticsearch/logstash

# 环境搭建

## Download & Install

下载并解压缩tar.gz即可: https://www.elastic.co/downloads/beats/filebeat

e.g.:

    flying-bird@flyingbird:~/elk$ tar -xzf filebeat-6.0.0-linux-x86.tar.gz 
    flying-bird@flyingbird:~/elk$ cd filebeat-6.0.0-linux-x86/
    flying-bird@flyingbird:~/elk/filebeat-6.0.0-linux-x86$ ls
    fields.yml  filebeat.reference.yml  kibana       module     NOTICE.txt
    filebeat    filebeat.yml            LICENSE.txt  modules.d  README.md
    flying-bird@flyingbird:~/elk/filebeat-6.0.0-linux-x86$ 

## 准备配置文件

创建Filebeat的配置目录，并以filebeat.reference.yml作为基准文件，修改得到所需要的配置文件。

    filebeat  logstash
    flying-bird@flyingbird:~/code_snippets/elk$ mkdir myconf
    flying-bird@flyingbird:~/code_snippets/elk$ cd myconf/
    flying-bird@flyingbird:~/code_snippets/elk/myconf$ mkdir -p filebeat/data filebeat/logs
    flying-bird@flyingbird:~/code_snippets/elk/myconf$ cp ~/elk/filebeat-6.0.0-linux-x86/filebeat.reference.yml filebeat/
    flying-bird@flyingbird:~/code_snippets/elk/myconf$ cp filebeat/filebeat.reference.yml filebeat/filebeat_01.yml
    flying-bird@flyingbird:~/code_snippets/elk/myconf$ 

修改filebeat_01.yml.

## 准备测试日志文件

    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat$ mkdir input_logs
    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat$ cd input_logs/
    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat/input_logs$ echo First line > test.log
    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat/input_logs$ echo Second line >> test.log
    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat/input_logs$ cat test.log
    First line
    Second line
    flying-bird@flyingbird:~/code_snippets/elk/myconf/filebeat/input_logs$ 

# 运行

    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml

Ctrl+C停止运行。输出结果参考filebeat_result_01.yml。


