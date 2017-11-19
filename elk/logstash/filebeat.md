# Overview

这里通过FileBeat把日志文件的数据发送给LogStash，LogStash不做任何处理，然后直接打印到控制台。

# Filebeat

FileBeat的安装和配置过程，参考[FileBeat](TODO).

# logstash.conf

input部分改成：

    input {
        beats {
            port => "5043"
        }
    }

    #filter {
    #}

    output {
        stdout { codec => rubydebug }
    }



