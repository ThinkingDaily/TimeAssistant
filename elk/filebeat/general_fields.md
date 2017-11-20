# Overview

这里主要介绍general部分的自定义字段(fields)，顺便介绍general的其它几个配置项。

# 配置

参考filebeat_03.yml，主要内容：

    #================================ General ======================================

    # The name of the shipper that publishes the network data. It can be used to group
    # all the transactions sent by a single shipper in the web interface.
    # If this options is not defined, the hostname is used.
    name: the_shipper

    # The tags of the shipper are included in their own field with each
    # transaction published. Tags make it easy to group servers by different
    # logical properties.
    #tags: ["service-X", "web-tier"]
    tags: ["my_tag1", "my_tag2"]

    # Optional fields that you can specify to add additional information to the
    # output. Fields can be scalar values, arrays, dictionaries, or any nested
    # combination of these.
    fields:
      env: staging
      general_field_x: "value with spaces"

    # If this option is set to true, the custom fields are stored as top-level
    # fields in the output document instead of being grouped under a fields
    # sub-dictionary. Default is false.
    fields_under_root: false

# 运行

    rm ~/code_snippets/elk/myconf/filebeat/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_03.yml

# 输出结果

和之前比较，结果多了几个字段: tags, fields.

    {
      "@timestamp": "2017-11-20T14:34:20.073Z",
      "@metadata": {
        "beat": "filebeat",
        "type": "doc",
        "version": "6.0.0"
      },
      "source": "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/test.log",
      "offset": 11,
      "message": "First line",
      "tags": [
        "my_tag1",
        "my_tag2"
      ],
      "prospector": {
        "type": "log"
      },
      "fields": {
        "general_field_x": "value with spaces",
        "env": "staging"
      },
      "beat": {
        "version": "6.0.0",
        "name": "the_shipper",
        "hostname": "flyingbird"
      }
    }

# fields_under_root

如果把fields_under_root改为true，那么结果如下：

    {
      "@timestamp": "2017-11-20T14:37:45.644Z",
      "@metadata": {
        "beat": "filebeat",
        "type": "doc",
        "version": "6.0.0"
      },
      "beat": {
        "name": "the_shipper",
        "hostname": "flyingbird",
        "version": "6.0.0"
      },
      "message": "First line",
      "source": "/home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/test.log",
      "offset": 11,
      "tags": [
        "my_tag1",
        "my_tag2"
      ],
      "prospector": {
        "type": "log"
      },
      "env": "staging",
      "general_field_x": "value with spaces"
    }

注意general中两个字段的位置发生了变化，现在处于root级别。


