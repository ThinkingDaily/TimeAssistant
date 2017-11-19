Kibana

# Installation

- Download tar.gz from https://github.com/elastic/kibana
- tar -xzf kibana-5.5.2-linux-x86_64.tar.gz
- cd kibana/
- ./bin/kibana

# Web Access

Kibana缺省访问端口是5601。第一次运行时会要求设置index的名字或pattern。

# Dev Tools

在Dev Tools中可以执行Elasticsearch的各种命令。

Kibana使用简洁命令，但也可以使用curl命令。但不能把curl命令拷贝到Kibana，——后者会自动裁剪成简洁命令。

# Example

    $ ./bin/kibana
    [plugin:kibana@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:elasticsearch@5.5.2] Status changed from uninitialized to yellow - Waiting for Elasticsearch
    [plugin:console@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:metrics@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:timelion@5.5.2] Status changed from uninitialized to green - Ready
    [listening] Server running at http://localhost:5601
    [ui settings] Status changed from uninitialized to yellow - Elasticsearch plugin is yellow
    [plugin:elasticsearch@5.5.2] Status changed from yellow to green - Kibana index ready
    [ui settings] Status changed from yellow to green - Ready

# 设置

可以从原版本中拷贝一份config/kibana.yml，然后新建自己的data & logs目录，并全部配置在yml中。

其中logs是实际的文件，而不是目录。

修改config/kibana.yml，其中缺省没有path.data，可以自己添加，参考：

    https://www.elastic.co/guide/en/kibana/current/settings.html

配置文件好了之后：

    ./bin/kibana --config /your_dir/config/kibana.yml

另外，一开始可以不用设置logging.dest，这样直接在控制台上观察Kibana的日志。等运行成功之后，再设置日志文件。