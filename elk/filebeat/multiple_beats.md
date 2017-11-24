# Overview

要在一台机器上运行多个Filebeat进程，那么只需要每个进程有自己的data目录即可。——实际情况下，还有对应的yml文件。

# Example

这里以prospector_fields.md以及filebeat_04.yml为基准，拆分成foo、bar_log、bar_err三个配置文件，并运行对应的三个独立的Filebeat实例，数据都发送给Logstash。

## 配置文件

- myconf/filebeat/filebeat_foo.yml
- myconf/filebeat/filebeat_bar_log.yml
- myconf/filebeat/filebeat_bar_err.yml

## Running

    rm ~/code_snippets/elk/myconf/filebeat/foobar/foo/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_foo.yml
    
    rm ~/code_snippets/elk/myconf/filebeat/foobar/bar_log/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_bar_log.yml
    
    rm ~/code_snippets/elk/myconf/filebeat/foobar/bar_err/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_bar_err.yml
    
logstash使用logstash_01.conf配置文件:

    ~/elk/logstash-6.0.0/bin/logstash --path.settings ~/code_snippets/elk/myconf/logstash/config -f ~/code_snippets/elk/myconf/logstash/logstash_01.conf 

运行结果：
    
    {
        "@timestamp" => 2017-11-24T14:08:12.504Z,
            "offset" => 7,
          "@version" => "1",
              "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
              "host" => "flyingbird",
        "prospector" => {
            "type" => "log"
        },
            "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/foo/test.log",
           "message" => "Foo 1.",
            "fields" => {
            "foo_level" => "foo_info",
                  "env" => "staging",
              "foo_app" => "foo"
        },
              "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
        "@timestamp" => 2017-11-24T14:08:12.504Z,
            "offset" => 14,
          "@version" => "1",
              "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
              "host" => "flyingbird",
        "prospector" => {
            "type" => "log"
        },
            "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/foo/test.log",
           "message" => "Foo 2.",
            "fields" => {
            "foo_level" => "foo_info",
                  "env" => "staging",
              "foo_app" => "foo"
        },
              "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
          "bar_err_app" => "bar",
           "@timestamp" => 2017-11-24T14:08:38.968Z,
        "bar_err_level" => "error",
               "offset" => 11,
             "@version" => "1",
                 "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
                 "host" => "flyingbird",
           "prospector" => {
            "type" => "log"
        },
               "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/bar.err",
              "message" => "bar err 1.",
               "fields" => {
            "env" => "staging"
        },
                 "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
          "bar_err_app" => "bar",
           "@timestamp" => 2017-11-24T14:08:38.969Z,
               "offset" => 22,
        "bar_err_level" => "error",
             "@version" => "1",
                 "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
                 "host" => "flyingbird",
           "prospector" => {
            "type" => "log"
        },
               "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/bar.err",
              "message" => "bar err 2.",
               "fields" => {
            "env" => "staging"
        },
                 "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
           "@timestamp" => 2017-11-24T14:09:01.128Z,
               "offset" => 11,
          "bar_log_app" => "bar",
             "@version" => "1",
                 "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
                 "host" => "flyingbird",
           "prospector" => {
            "type" => "log"
        },
               "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/bar.log",
              "message" => "bar log 1.",
               "fields" => {
                      "env" => "staging",
            "bar_log_level" => "info",
              "bar_log_app" => "bar"
        },
        "bar_log_level" => "info",
                 "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    {
        "@timestamp" => 2017-11-24T14:09:01.128Z,
            "offset" => 22,
          "@version" => "1",
              "beat" => {
                "name" => "the_shipper",
            "hostname" => "flyingbird",
             "version" => "6.0.0"
        },
              "host" => "flyingbird",
        "prospector" => {
            "type" => "log"
        },
            "source" => "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/bar/bar.log",
           "message" => "bar log 2.",
            "fields" => {
                      "env" => "staging",
            "bar_log_level" => "info",
              "bar_log_app" => "bar"
        },
              "tags" => [
            [0] "beats_input_codec_plain_applied"
        ]
    }
    
