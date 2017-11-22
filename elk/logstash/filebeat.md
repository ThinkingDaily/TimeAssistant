# Overview

这里通过FileBeat把日志文件的数据发送给LogStash，LogStash不做任何处理，然后直接打印到控制台。

# Filebeat

FileBeat的安装和配置过程，参考filebeat/logstash.md.

# 配置文件

3个目录(config&data&logs)和一个文件(conf).

    flying-bird@flyingbird:~/code_snippets/elk/myconf/logstash$ cp -rf ~/elk/logstash-6.0.0/config .
    flying-bird@flyingbird:~/code_snippets/elk/myconf/logstash$ mkdir data logs
    flying-bird@flyingbird:~/code_snippets/elk/myconf/logstash$ 

conf文件：

    myconf/logstash/logstash_01.conf

即：

    input {
        beats {
            port => "5044"
        }
    }

    #filter {
    #}

    output {
        stdout { codec => rubydebug }
    }

# 运行

    ~/elk/logstash-6.0.0/bin/logstash --path.settings ~/code_snippets/elk/myconf/logstash/config -f ~/code_snippets/elk/myconf/logstash/logstash_01.conf 

Detail:

    flying-bird@flyingbird:~$ ~/elk/logstash-6.0.0/bin/logstash --path.settings ~/code_snippets/elk/myconf/logstash/config -f ~/code_snippets/elk/myconf/logstash/logstash_01.conf 
    Sending Logstash's logs to /home/flying-bird/code_snippets/elk/myconf/logstash/logs which is now configured via log4j2.properties
    [2017-11-22T23:10:45,311][INFO ][logstash.modules.scaffold] Initializing module {:module_name=>"netflow", :directory=>"/home/flying-bird/elk/logstash-6.0.0/modules/netflow/configuration"}
    [2017-11-22T23:10:45,315][INFO ][logstash.modules.scaffold] Initializing module {:module_name=>"fb_apache", :directory=>"/home/flying-bird/elk/logstash-6.0.0/modules/fb_apache/configuration"}
    [2017-11-22T23:10:45,392][INFO ][logstash.setting.writabledirectory] Creating directory {:setting=>"path.queue", :path=>"/home/flying-bird/code_snippets/elk/myconf/logstash/data/queue"}
    [2017-11-22T23:10:45,395][INFO ][logstash.setting.writabledirectory] Creating directory {:setting=>"path.dead_letter_queue", :path=>"/home/flying-bird/code_snippets/elk/myconf/logstash/data/dead_letter_queue"}
    [2017-11-22T23:10:45,742][WARN ][logstash.config.source.multilocal] Ignoring the 'pipelines.yml' file because modules or command line options are specified
    [2017-11-22T23:10:45,765][INFO ][logstash.agent           ] No persistent UUID file found. Generating new UUID {:uuid=>"5e833d98-10db-4eb3-8afa-ff0757bc6dbd", :path=>"/home/flying-bird/code_snippets/elk/myconf/logstash/data/uuid"}
    [2017-11-22T23:10:46,256][INFO ][logstash.agent           ] Successfully started Logstash API endpoint {:port=>9600}
    [2017-11-22T23:10:47,559][INFO ][logstash.pipeline        ] Starting pipeline {:pipeline_id=>"main", "pipeline.workers"=>2, "pipeline.batch.size"=>125, "pipeline.batch.delay"=>5, "pipeline.max_inflight"=>250, :thread=>"#<Thread:0x1797faf@/home/flying-bird/elk/logstash-6.0.0/logstash-core/lib/logstash/pipeline.rb:290 run>"}
    [2017-11-22T23:10:47,689][INFO ][logstash.inputs.beats    ] Beats inputs: Starting input listener {:address=>"0.0.0.0:5044"}
    [2017-11-22T23:10:48,103][INFO ][logstash.pipeline        ] Pipeline started {"pipeline.id"=>"main"}
    [2017-11-22T23:10:48,131][INFO ][logstash.agent           ] Pipelines running {:count=>1, :pipelines=>["main"]}
    [2017-11-22T23:10:48,153][INFO ][org.logstash.beats.Server] Starting server on port: 5044

如果这里看不到日志输出，那么检查filebeat的配置文件，或者删除regsitry后重现运行filebeat。

logstash输出的日志如下：

    {
        "@timestamp" => 2017-11-22T15:13:47.367Z,
            "offset" => 11,
          "@version" => "1",
              "beat" => {
                "name" => "flyingbird",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
              "host" => "flyingbird",
        "prospector" => {
            "type" => "log"
        },
            "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/test.log",
           "message" => "First line",
              "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
        "@timestamp" => 2017-11-22T15:13:47.367Z,
            "offset" => 23,
          "@version" => "1",
              "beat" => {
                "name" => "flyingbird",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
              "host" => "flyingbird",
        "prospector" => {
            "type" => "log"
        },
            "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/test.log",
           "message" => "Second line",
              "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }

至此，把filebeat和logstash两者的通道打通了。Ctrl+C，终止Logstash的运行。

    ^C[2017-11-22T23:16:27,129][WARN ][logstash.runner          ] SIGINT received. Shutting down the agent.
    [2017-11-22T23:16:32,136][WARN ][logstash.runner          ] Received shutdown signal, but pipeline is still waiting for in-flight events
    to be processed. Sending another ^C will force quit Logstash, but this may cause
    data loss.
    [2017-11-22T23:16:32,194][WARN ][logstash.shutdownwatcher ] {"inflight_count"=>0, "stalling_thread_info"=>{"other"=>[{"thread_id"=>26, "name"=>"[main]<beats", "current_call"=>"[...]/vendor/bundle/jruby/2.3.0/gems/logstash-input-beats-5.0.2-java/lib/logstash/inputs/beats.rb:196:in `run'"}, {"thread_id"=>24, "name"=>"[main]>worker0", "current_call"=>"[...]/logstash-core/lib/logstash/util/wrapped_synchronous_queue.rb:112:in `lock'"}, {"thread_id"=>25, "name"=>"[main]>worker1", "current_call"=>"[...]/logstash-core/lib/logstash/util/wrapped_synchronous_queue.rb:112:in `lock'"}]}}
    [2017-11-22T23:16:32,196][ERROR][logstash.shutdownwatcher ] The shutdown process appears to be stalled due to busy or blocked plugins. Check the logs for more information.
    [2017-11-22T23:16:33,657][INFO ][logstash.pipeline        ] Pipeline terminated {"pipeline.id"=>"main"}
    