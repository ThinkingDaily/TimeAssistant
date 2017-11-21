kibana-installation

# Download & Install

    wget https://artifacts.elastic.co/downloads/kibana/kibana-6.0.0-linux-x86_64.tar.gz
    tar -xzf kibana-6.0.0-linux-x86_64.tar.gz
    cd kibana-6.0.0-linux-x86_64/

# Run

基本命令：

    ./bin/kibana

但通常都要先配置本地的config/data/logs之后，再运行。见本文最后。

# Stop

Ctrl+C

# Configuration File

## Ref

https://www.elastic.co/guide/en/kibana/6.0/settings.html

## 自定义配置

缺省的配置文件：$KIBANA_HOME/config/kibana.yml。但通常用自己的一套目录，比如：

    kibana-learn user$ mkdir -p mykibana/data mykibana/logs
    kibana-learn user$ cp -rf /your/dir/kibana-5.5.2-darwin-x86_64/config mykibana/
    kibana-learn user$ ls mykibana/config/kibana.yml 
    mykibana/config/kibana.yml
    kibana-learn user$ 

然后修改kibana.yml文件，主要包括：

- Elasticsearch的host & port
- Kibana对外提供服务的port
- data/logs路径，其中path.data在缺省yml中没有，需要自己添加。

Kibana不需要配置config目录，因为config下只有yml文件，而这个yml是在启动的时候通过命令行指定。

# Running

## 命令

    /your/dir/kibana-5.5.2-darwin-x86_64/bin/kibana --config /your/dir/mykibana/config/kibana.yml &

第一次运行的时候，不要加&，待验证通过之后，再&后台运行。

## log

如果在yml中禁掉了stdout log，那么控制台上看不到任何Kibana日志。

    # Enables you specify a file where Kibana stores log output.
    #logging.dest: stdout
    logging.dest: /your/dir/mykibana/logs/kibana.log

此时，可以在指定的日志文件中查看运行结果。

## 验证

浏览器访问http://localhost:5601（和yml配置的端口号保持一致）。以此判断Kibana是否运行起来了。

注：即便日志中提示Elasticsearch连不上，同样可以访问5601。