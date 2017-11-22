# Overview

general fields是应用于Filebeat程序处理的每一条记录。进一步地，Filebeat可以定义多个input，如多种日志文件，然后为每种日志文件定义自己的一些字段。

# Example

假定机器上有两个应用程序foo和bar，其中foo的日志统一为\*.log，而bar的日志包括两种，即\*.log和\*.err。

# 配置文件

参考filebeat_04.yml。主要修改如下：

    filebeat.prospectors:

    - type: log
      enabled: true
      paths:
        - /home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/foo/*.log
      fields:
        foo_level: foo_info
        foo_app: foo
      fields_under_root: false

    - type: log
      enabled: true
      paths:
        - /home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/*.log
      fields:
        bar_log_level: info
        bar_log_app: bar
      fields_under_root: false

    - type: log
      enabled: true
      paths:
        - /home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/*.err
      fields:
        bar_err_level: error
        bar_err_app: bar
      fields_under_root: true

# 运行

    rm ~/code_snippets/elk/myconf/filebeat/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_04.yml

# 输出结果

观察filebeat\_result\_04.log，发现输出结果并非如预期。

# 进一步的探讨

接下来，将filebeat\_04.yml中的3个log部分直接归并，对应filebeat\_05.yml。但此时的输出，filebeat\_result\_05.log，更加出乎意料。

# 结论

在一个yml中，只配置一份log，其中path，field等只配置一套。进一步的信息，可以从日志本身的grok来实现。比如：

    [foo][log]foo log 1.
    [foo][log]foo log 2.
    [bar][log]bar log 1.
    [bar][log]bar log 2.
    [bar][err]bar err 1.
    [bar][err]bar err 2.

另外一一种规避方法，就是（在同一台机器上）启动Filebeat的多个实例，每个实例对应一个log配置。如启动3个实例，分别对应foo-log, bar-log, bar-err三种程序/日志类型。但显然，这远不如grok方式易于管理，且grok方式的可扩展性更高。
