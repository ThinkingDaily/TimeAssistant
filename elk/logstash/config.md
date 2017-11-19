# Overview

这里描述启动Logstash时，常用的配置项。

# 目录和文件

## Prepare

简单来讲，3个目录(config&data&logs)和一个文件(.conf)。其中，config直接从logstash tar.gz解压缩后拷贝过来，而data&logs是两个空目录。

——官网下载的logstash tar.gz中，包括data和config目录，其中data是空目录；没有logs目录。

    flying-bird@flyingbird:~/elk/logstash-5.5.2$ cd ..
    flying-bird@flyingbird:~/elk$ mkdir -p myconf/logstash/logs myconf/logstash/data 
    flying-bird@flyingbird:~/elk$ cp -rf logstash-5.5.2/config myconf/logstash/
    flying-bird@flyingbird:~/elk$ touch myconf/logstash/logstash.conf
    flying-bird@flyingbird:~/elk$ 

## Custom

接下来，修改缺省的config/logstash.yml文件，以及logstach.conf文件。

### logstash.yml

示例修改参考logstash_custom.yml，主要修改点(data&config&logs&reload\_automatic):

    # Which directory should be used by logstash and its plugins
    # for any persistent needs. Defaults to LOGSTASH_HOME/data
    #
    path.data: /home/flying-bird/elk/myconf/logstash/data
    #
    # ------------ Pipeline Configuration Settings --------------
    #
    # Where to fetch the pipeline configuration for the main pipeline
    #
    path.config: /home/flying-bird/elk/myconf/logstash/config
    #
    # Periodically check if the configuration has changed and reload the pipeline
    # This can also be triggered manually through the SIGHUP signal
    #
    config.reload.automatic: true
    #
    # ------------ Debugging Settings --------------
    #
    # log.level: info
    path.logs: /home/flying-bird/elk/myconf/logstash/logs

其中config.reload.automatic的功能在于，当conf配置文件的内容方式变化之后，不需要重新启动Logstash，而自动加载。

### logstash.conf

定义pipeline的文件，参考logstash_custom.conf。主要包括三部分: input & filter & output。

    input {
        stdin { }
    }

    #filter {
    #}

    output {
        stdout { codec => rubydebug }
    }

# Running

在创建了前面的目录和配置文件之后，启动：

    /home/flying-bird/elk/logstash-5.5.2/bin/logstash --path.config /home/flying-bird/elk/myconf/logstash/config -f /home/flying-bird/elk/myconf/logstash/logstash.conf

Detail:


    flying-bird@flyingbird:~/elk$ /home/flying-bird/elk/logstash-5.5.2/bin/logstash --path.config /home/flying-bird/elk/myconf/logstash/config -f /home/flying-bird/elk/myconf/logstash/logstash.conf
    ERROR StatusLogger No log4j2 configuration file found. Using default configuration: logging only errors to the console.
    Sending Logstash's logs to /home/flying-bird/elk/logstash-5.5.2/logs which is now configured via log4j2.properties
    [2017-11-19T21:43:30,595][INFO ][logstash.pipeline        ] Starting pipeline {"id"=>"main", "pipeline.workers"=>2, "pipeline.batch.size"=>125, "pipeline.batch.delay"=>5, "pipeline.max_inflight"=>250}
    [2017-11-19T21:43:30,620][INFO ][logstash.pipeline        ] Pipeline main started
    The stdin plugin is now waiting for input:
    [2017-11-19T21:43:30,679][INFO ][logstash.agent           ] Successfully started Logstash API endpoint {:port=>9600}
    Hello, Logstash!
    {
        "@timestamp" => 2017-11-19T13:43:36.492Z,
          "@version" => "1",
              "host" => "flyingbird",
           "message" => "Hello, Logstash!"
    }

Ctrl+C停止程序。

