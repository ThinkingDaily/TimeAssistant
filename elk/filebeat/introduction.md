# Ref

- Getting Started With Filebeat: https://www.elastic.co/guide/en/beats/filebeat/current/filebeat-getting-started.html
- 源码: https://github.com/elasticsearch/logstash

# 环境搭建

https://www.elastic.co/downloads/beats/filebeat

环境搭建：
- 下载并解压缩tar.gz即可: https://www.elastic.co/downloads/beats/filebeat
- 配置yml文件
- 后台运行：sudo ./filebeat -e -c filebeat.yml

通常还需要Elasticsearch，Kibana，Logstash。其中Filebeat的输出可以是Elasticsearch或Logstash。如果要对Filebeat的数据做二次处理，则输出到Logstash，然后再由Logstash发给Elasticsearch。

# 命令行选项

Ref: [https://www.elastic.co/guide/en/beats/filebeat/current/command-line-options.html](https://www.elastic.co/guide/en/beats/filebeat/current/command-line-options.html)

常用的：

    -c <file>
    Pass the location of a configuration file for the Beat.
    指定配置文件(*.yml)

    -configtest
    Test the configuration file and then exit. This option is useful for troubleshooting the configuration of a Beat.
    仅检查配置文件

    -d <selectors>
    Enable debugging for the specified selectors. For the selectors, you can specify a comma-separated list of components, or you can use -d "*" to enable debugging for all components. For example, -d "publish" displays all the "publish" related messages.

    -e
    Log to stderr and disable syslog/file output.

# 配置文件

Filebeat需要一个.yml配置文件。

以根目录下的filebeat.yml或者filebeat.full.yml为底本，新建一个配置文件，如log_filebeat.yml

    filebeat.prospectors:
    - input_type: log
      paths:
        - /your_log_directory/*.log
    output.logstash:
      hosts: ["localhost:5043"]

这里是读取指定目录下的所有.log文件，每一行对应一个Event，发给Logstash。Filebeat和Logstash约定的端口号是5043，——当然，双方也可约定其它的端口号。

需要注意的是，这里的路径不能用相对路径，不能用'~/your_dir/\*.log'，必须把'~'改成绝对路径，否则FileBeat无法捕获日志文件。

验证配置是否正确：用configtest来检查yml配置文件是否合法。此外，要求yml的owner要是root。

命令：

    sudo ./filebeat -configtest -e -c /your_yml_dir/log_filebeat.yml 
    sudo chown root /your_yml_dir/log_filebeat.yml 
    sudo ./filebeat -configtest -e -c /your_yml_dir/log_filebeat.yml 

Detail:

    $ sudo ./filebeat -configtest -e -c /your_config_dir/log_filebeat.yml 
    Password:
    filebeat2017/08/30 03:08:16.898775 beat.go:339: CRIT Exiting: error loading config file: config file ("../filebeat_ex/log_filebeat.yml") must be owned by the beat user (uid=0) or root
    Exiting: error loading config file: config file ("../filebeat_ex/log_filebeat.yml") must be owned by the beat user (uid=0) or root
    $ 
    $ sudo chown root /your_config_dir/log_filebeat.yml 
    $ sudo ./filebeat -configtest -e -c /your_config_dir/log_filebeat.yml 
    2017/08/30 03:10:07.180233 beat.go:285: INFO Home path: [/your_filebeat_directory/filebeat-5.5.2-darwin-x86_64] Config path: [/your_filebeat_directory/filebeat-5.5.2-darwin-x86_64] Data path: [/your_filebeat_directory/filebeat-5.5.2-darwin-x86_64/data] Logs path: [/your_filebeat_directory/filebeat-5.5.2-darwin-x86_64/logs]
    2017/08/30 03:10:07.180265 beat.go:186: INFO Setup Beat: filebeat; Version: 5.5.2
    2017/08/30 03:10:07.180287 metrics.go:23: INFO Metrics logging every 30s
    2017/08/30 03:10:07.180328 logstash.go:90: INFO Max Retries set to: 3
    2017/08/30 03:10:07.180659 outputs.go:108: INFO Activated logstash as output plugin.
    2017/08/30 03:10:07.180943 publish.go:295: INFO Publisher name: user.local
    2017/08/30 03:10:07.182022 async.go:63: INFO Flush Interval set to: 1s
    2017/08/30 03:10:07.182035 async.go:64: INFO Max Bulk Size set to: 2048
    Config OK
    $ 

Ref:

    sudo chmod go-w my_filebeat.yml

# 测试日志文件

创建test.log，增加一行内容：

    83.149.9.216 - - [04/Jan/2015:05:13:42 +0000] "GET /presentations/logstash-monitorama-2013/images/kibana-search.png HTTP/1.1" 200 203023 "http://semicomplete.com/presentations/logstash-monitorama-2013/" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.77 Safari/537.36"

注对应的模式如下，具体参考Logstash的grok介绍：

    HTTPD_COMMONLOG %{IPORHOST:clientip} %{HTTPDUSER:ident} %{HTTPDUSER:auth} \[%{HTTPDATE:timestamp}\] "(?:%{WORD:verb} %{NOTSPACE:request}(?: HTTP/%{NUMBER:httpversion})?|%{DATA:rawrequest})" %{NUMBER:response} (?:%{NUMBER:bytes}|-)
    HTTPD_COMBINEDLOG %{HTTPD_COMMONLOG} %{QS:referrer} %{QS:agent}
    COMBINEDAPACHELOG %{HTTPD_COMBINEDLOG}

# 运行

再次运行FileBeat，这次去掉configtest选项：

    $ sudo ./filebeat -e -c /your_yml_dir/log_filebeat.yml 
    Password:
    2017/11/09 01:35:47.148727 beat.go:285: INFO Home path: [.../filebeat-5.5.2-darwin-x86_64] Config path: [.../filebeat-5.5.2-darwin-x86_64] Data path: [.../filebeat-5.5.2-darwin-x86_64/data] Logs path: [.../filebeat-5.5.2-darwin-x86_64/logs]
    2017/11/09 01:35:47.148759 beat.go:186: INFO Setup Beat: filebeat; Version: 5.5.2
    2017/11/09 01:35:47.148813 logstash.go:90: INFO Max Retries set to: 3
    2017/11/09 01:35:47.148860 outputs.go:108: INFO Activated logstash as output plugin.
    2017/11/09 01:35:47.148925 publish.go:295: INFO Publisher name: ...
    2017/11/09 01:35:47.149013 async.go:63: INFO Flush Interval set to: 1s
    2017/11/09 01:35:47.149031 async.go:64: INFO Max Bulk Size set to: 2048
    2017/11/09 01:35:47.149430 metrics.go:23: INFO Metrics logging every 30s
    2017/11/09 01:35:47.149561 beat.go:221: INFO filebeat start running.
    2017/11/09 01:35:47.149590 registrar.go:85: INFO Registry file set to: .../filebeat-5.5.2-darwin-x86_64/data/registry
    2017/11/09 01:35:47.150257 registrar.go:106: INFO Loading registrar data from .../filebeat-5.5.2-darwin-x86_64/data/registry
    2017/11/09 01:35:47.153117 registrar.go:123: INFO States Loaded from registrar: 3
    2017/11/09 01:35:47.153176 registrar.go:236: INFO Starting Registrar
    2017/11/09 01:35:47.153225 spooler.go:63: INFO Starting spooler: spool_size: 2048; idle_timeout: 5s
    2017/11/09 01:35:47.153141 crawler.go:38: INFO Loading Prospectors: 1
    2017/11/09 01:35:47.153181 sync.go:41: INFO Start sending events to output
    2017/11/09 01:35:47.417341 prospector_log.go:65: INFO Prospector with previous states loaded: 0
    2017/11/09 01:35:47.417947 prospector.go:124: INFO Starting prospector of type: log; id: 12965195101599504345 
    2017/11/09 01:35:47.417964 crawler.go:58: INFO Loading and starting Prospectors completed. Enabled prospectors: 1

如果配置正确，且已经增加了测试log文件的话，这里会打印：

    2017/11/09 02:43:37.678812 log.go:91: INFO Harvester started for file: .../test_logs/test.log

否则，就要再去检查yml文件。

接下来配置LogStash，用以接收FileBeat的数据。回到Logstash.

