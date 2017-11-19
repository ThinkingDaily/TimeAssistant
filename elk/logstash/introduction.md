# Ref

- docs: https://www.elastic.co/guide/en/logstash/current/index.html
- Getting Started: https://www.elastic.co/guide/en/logstash/current/getting-started-with-logstash.html
- 中文入门素材： https://kibana.logstash.es/content/logstash/index.html

# 周边依赖

Logstash可以单独运行，调试完毕之后，再通过elasticsearch插件和Elasticsearch对接。

# Installation

- 下载tar.gz: https://www.elastic.co/cn/downloads/logstash
- 解压缩tar.gz
- 运行bin/logstash

# Example: Hello, world!
          
    flying-bird@flyingbird:~/elk/logstash-5.5.2$ ./bin/logstash -e 'input { stdin { } } output { stdout {} }'
    ERROR StatusLogger No log4j2 configuration file found. Using default configuration: logging only errors to the console.
    Sending Logstash's logs to /home/flying-bird/elk/logstash-5.5.2/logs which is now configured via log4j2.properties
    [2017-11-18T13:24:08,778][INFO ][logstash.setting.writabledirectory] Creating directory {:setting=>"path.queue", :path=>"/home/flying-bird/elk/logstash-5.5.2/data/queue"}
    [2017-11-18T13:24:08,783][INFO ][logstash.setting.writabledirectory] Creating directory {:setting=>"path.dead_letter_queue", :path=>"/home/flying-bird/elk/logstash-5.5.2/data/dead_letter_queue"}
    [2017-11-18T13:24:08,837][INFO ][logstash.agent           ] No persistent UUID file found. Generating new UUID {:uuid=>"d2f8e473-491d-474e-bc5a-3c7ee65d2063", :path=>"/home/flying-bird/elk/logstash-5.5.2/data/uuid"}
    [2017-11-18T13:24:09,003][INFO ][logstash.pipeline        ] Starting pipeline {"id"=>"main", "pipeline.workers"=>2, "pipeline.batch.size"=>125, "pipeline.batch.delay"=>5, "pipeline.max_inflight"=>250}
    The stdin plugin is now waiting for input:
    [2017-11-18T13:24:09,041][INFO ][logstash.pipeline        ] Pipeline main started
    [2017-11-18T13:24:09,104][INFO ][logstash.agent           ] Successfully started Logstash API endpoint {:port=>9600}
    Hello, world! <---- Your Input
    2017-11-18T05:24:25.700Z flyingbird Hello, world! <---- The Output

Ctrl+C退出程序。

    ^C[2017-11-18T13:24:29,781][WARN ][logstash.runner          ] SIGINT received. Shutting down the agent.
    [2017-11-18T13:24:29,796][WARN ][logstash.agent           ] stopping pipeline {:id=>"main"}
    flying-bird@flyingbird:~/elk/logstash-5.5.2$ 
