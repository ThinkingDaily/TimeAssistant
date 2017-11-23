Logstash可以接收多个同一端口的Filebeat发过来的数据，也可以支持多个Filebeat的多个端口发过来的数据。

为此，在input部分定义多个beats插件即可：

    input {
        beats {
            port => "5043"
        }
        beats {
            port => "5044"
        }
    }

但通常没有这种需求。