filebeat-启动项

# Ref

- https://www.elastic.co/guide/en/beats/filebeat/current/command-line-options.html

# help

    $ ./filebeat --help
    Usage of ./filebeat:
      -E value
            Configuration overwrite (default null)
      -M value
            Module configuration overwrite (default null)
      -N    Disable actual publishing for testing

      -c value
            Configuration file, relative to path.config (default filebeat.yml)
            指定yml配置文件，配置文件包括了input&output。

      -configtest
            Test configuration and exit.
            测试配置文件的合法性，然后退出程序。
            6.0及以后版本使用test config子命令。

      -cpuprofile string
            Write cpu profile to file

      -d string
            Enable certain debug selectors

      -e    Log to stderr and disable syslog/file output
            记录日志都stderr，并禁掉syslog/file输出。

      -httpprof string
            Start pprof http server
      -memprofile string
            Write memory profile to this file
      -modules string
            List of enabled modules (comma separated)

      -once
            Run filebeat only once until all harvesters reach EOF
            仅运行一次filebeat，当文件读完之后，就退出。

      -path.config value
            Configuration path

      -path.data value
            Data path

      -path.home value
            Home path

      -path.logs value
            Logs path

      -setup
            Load the sample Kibana dashboards
            把sample kibana dashboards加载到Kibana，然后退出。通常在搭建环境的初期，执行这个步骤。
            另外一种情况，配置文件中启用output Elasticsearch，在Elasticsearch中创建index template。
            当然，也可以手动在Elasticsearch中创建index template。
            配置完Elasticsearch之后，就把这个output禁掉，然后启用Logstash output。

      -strict.perms
            Strict permission checking on config files (default true)

      -v    Log at INFO level
      
      -version
            Print the version and exit
    $ 


# -e

help中的说明：

    "input { stdin { type => stdin } }"
    and if no output is specified, then the
    following is used as the default output:
    "output { stdout { codec => rubydebug } }"
    If you wish to use both defaults, please use
    the empty string for the '-e' flag.
    (default: nil)

即缺省值为："input { stdin { type => stdin } } output { stdout { codec => rubydebug } }"
