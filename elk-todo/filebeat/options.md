filebeat-启动项

# 普通日志文件的处理

http://www.elastic.co/guide/en/beats/filebeat/5.5/filebeat-modules-quickstart.html

# 文件修改

    $ ls -l
    total 31856
    -rw-r--r--@ 1 user  staff     97026 11  1 02:48 NOTICE
    -rw-r--r--@ 1 user  staff       811 11  1 02:49 README.md
    drwxr-x---  3 root       staff       102 11 17 10:38 data
    -rwxr-xr-x@ 1 user  staff  16088016 11  1 02:49 filebeat
    -rw-r--r--@ 1 user  staff     38827 11  1 02:49 filebeat.full.yml
    -rw-r--r--@ 1 user  staff     25087 11  1 02:49 filebeat.template-es2x.json
    -rw-r--r--@ 1 user  staff     20027 11  1 02:49 filebeat.template-es6x.json
    -rw-r--r--@ 1 user  staff     20027 11  1 02:49 filebeat.template.json
    -rw-------@ 1 user  staff      4196 11  1 02:49 filebeat.yml
    drwxr-xr-x@ 7 user  staff       238 11  1 02:40 module
    drwxr-xr-x@ 4 user  staff       136 11  1 02:49 scripts
    $

运行时，会使用到data目录。

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