# Overview

日志格式探讨。

# Filebeat

TODO

# Logstash

[2017-08-28T10:45:01,402][ERROR][logstash.agent           ] Cannot create pipeline {:reason=>"Expected one of #, input, filter, output at line 6, column 1 (byte 132) after ## JVM configuration\n\n# Xms represents the initial size of total heap space\n# Xmx represents the maximum size of total heap space\n\n"}
[2017-08-28T10:59:40,251][WARN ][logstash.agent           ] stopping pipeline {:id=>"main"}

[%d{ISO8601}][%-5p][%-25c] %-.10000m%n
时间戳 日志级别 类名 消息 换行

# Kibana

{"type":"log","@timestamp":"2017-08-26T00:54:01Z","tags":["status","plugin:kibana@5.5.2","info"],"pid":42049,"state":"green","message":"Status changed from uninitialized to green - Ready","prevState":"uninitialized","prevMsg":"uninitialized"}
{"type":"log","@timestamp":"2017-08-26T00:54:01Z","tags":["status","plugin:elasticsearch@5.5.2","info"],"pid":42049,"state":"yellow","message":"Status changed from uninitialized to yellow - Waiting for Elasticsearch","prevState":"uninitialized","prevMsg":"uninitialized"}

# Elasticsearch

[2017-08-22T12:27:55,567][INFO ][o.e.n.Node               ] [] initializing ...
[2017-08-22T14:07:23,605][INFO ][o.e.n.Node               ] initialized
[2017-08-22T14:07:23,605][INFO ][o.e.n.Node               ] [f0AumJt] starting ...
[2017-08-22T14:07:22,710][INFO ][o.e.x.m.j.p.l.CppLogMessageHandler] [controller/35513] [Main.cc@128] controller (64 bit): Version 5.5.0 (Build 9352b273163d45) Copyright (c) 2017 Elasticsearch BV

[%d{ISO8601}][%-5p][%-25c{1.}] %marker%m%n
时间戳 日志级别 类名 marker 消息 换行

# 建议

    [timestamp][DEBUG|INFO|WARN|ERROR][program_name][FILE:LINE]Message
