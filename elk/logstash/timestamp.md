# Overview

如果设置output为Elasticsearch，那么不能删除event中的@timestamp。

# 现象 

logstash接收日志并往Elasticsearch存储的时候，Logstash异常终止。日志如下：

    [FATAL][logstash.runner          ] 
    An unexpected error occurred! 
    {:error=>#<LogStash::Error: timestamp field is missing>, 
    :backtrace=>["org/logstash/ext/JrubyEventExtLibrary.java:205:in `sprintf'", 
    ".../logstash-5.6.4/vendor/bundle/jruby/1.9/gems/logstash-output-elasticsearch-7.4.2-java/lib/logstash/outputs/elasticsearch/common.rb:168:in `event_action_params'"...

# 分析

日志已经给出了原因：

    LogStash::Error: timestamp field is missing

即往Elasticsearch存储的doc丢失了timestamp字段。进一步地，是因为grok中配置为把这个字段删除：

    filter {
        grok {
            ...
            remove_field => [ "@timestamp" ]
        }
    }

# 解决办法

logstash conf文件中不要把@timestamp删除掉。

# @timestamp

在Kibana中，需要根据@timestamp做各种数据分析，因此这个字段不可缺少。
