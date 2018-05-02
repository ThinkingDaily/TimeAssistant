# Overview

本文讨论date filter的使用方法。

# Question

先看示例：

    2017-11-23T22:34:34,977
    {
        "@timestamp" => 2017-11-25T02:13:57.947Z,
             "month" => "11",
              "hour" => "22",
              "year" => "2017",
          "@version" => "1",
              "host" => "flyingbird",
           "message" => "2017-11-23T22:34:34,977",
               "day" => "23",
            "minute" => "34",
            "second" => "34,977"
    }

观察到，输入的时间和logstash生成的事件的@timestamp不一致。

# Analysis

Logstash是生成事件时，其时间戳为读取该记录时的时间戳，而和该记录本身的时间信息没有任何关系。——考虑到有些日志记录根本没有时间信息就可以理解了。

但为了后续数据分析的原因，我们又希望最终的事件取日志记录中的时间。即本例中，希望@timestamp等于输入的2017-11-23T22:34:34,977。

为此，可以借助date filter。

# date filter

## Ref

- https://www.elastic.co/guide/en/logstash/current/plugins-filters-date.html

## Description

The date filter is used for parsing dates from fields, and then using that date or timestamp as the logstash timestamp for the event.

In the absence of this filter, logstash will choose a timestamp based on the first time it sees the event (at input time), if the timestamp is not already set in the event. For example, with file input, the timestamp is set to the time of each read.

# Refactor

# 配置文件

现在对之前的配置文件进行优化，得到 logstash_dt_02.conf。

# 运行

~/elk/logstash-6.0.0/bin/logstash --path.settings ~/code_snippets/elk/myconf/logstash/config -f ~/code_snippets/elk/myconf/logstash/logstash_dt_02.conf 

# 测试数据

    2017-11-23T22:34:34,977
    2017-11-23 22:73:34.977
    2017-11-23 22:3a:34.977

# Result

see logstash_dt_02.result，如下：

    2017-11-23T22:34:34,977
    {
        "@timestamp" => 2017-11-23T14:34:34.977Z,
          "@version" => "1",
              "host" => "flyingbird",
           "message" => "2017-11-23T22:34:34,977"
    }
    2017-11-23 22:73:34.977
    {
        "@timestamp" => 2017-11-25T02:33:17.921Z,
          "@version" => "1",
              "host" => "flyingbird",
           "temp_ts" => "2017-11-23 22:73:34.977",
           "message" => "2017-11-23 22:73:34.977",
              "tags" => [
            [0] "_dateparsefailure"
        ]
    }
    2017-11-23 22:3a:34.977
    {
          "@version" => "1",
              "host" => "flyingbird",
        "@timestamp" => 2017-11-25T02:33:26.745Z,
           "message" => "2017-11-23 22:3a:34.977",
              "tags" => [
            [0] "_grokparsefailure"
        ]
    }

可以看到，当输入日期时间格式合法时，可以得到正确的@timestamp(注意到时区)。

# Next Step

接下来分析各种解析结果下的处理程序。
