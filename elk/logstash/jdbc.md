Logstash - JDBC

# jdbc

Logstash的JDBC说明: https://www.elastic.co/guide/en/logstash/5.5/plugins-inputs-jdbc.html

从MariaDB或MySQL官网下载jdbc的jar包，然后Logstash的input部分定义jdbc。

## Flows

    MySQL --> JDBC --> Logstash --> Elasticsearch
                                --> File
                                --> stdout
## Command

    bin/logstash -f first-pipeline.conf --config.reload.automatic

## MariaDB

- driver library: https://downloads.mariadb.com/Connectors/java/connector-java-2.1.0/mariadb-java-client-2.1.0.jar
- drive class: 解压缩jar，然后 META-INF/services/java.sql.Driver 中包括了 org.mariadb.jdbc.Driver
- connection string: 参考Core Java Volumn II, Database Programming. Syntax: jdbc:subprotocol:other stuff
  where a subprotocol selects the specific driver for connecting to the database.

    jdbc {
        jdbc_driver_library => "/.../mariadb-java-client-2.1.0.jar"
        #jdbc_driver_class => "com.mysql.jdbc.Driver"
        jdbc_driver_class => "org.mariadb.jdbc.Driver"
        jdbc_connection_string => "jdbc:mariadb://localhost:3306/test_db"
        jdbc_user => "root"
        parameters => { "city" => "SH" }
        schedule => "* * * * *"
        statement => "SELECT id, name, age, city FROM employee WHERE city = :city"
        use_column_value => true
        tracking_column => "id"
    }

## yml全文

    # The # character at the beginning of a line indicates a comment. Use
    # comments to describe your configuration.
    input {
        beats {
            port => "5043"
        }
        jdbc {
            jdbc_driver_library => "/.../mariadb-java-client-2.1.0.jar"
            jdbc_driver_class => "org.mariadb.jdbc.Driver"
            jdbc_connection_string => "jdbc:mariadb://localhost:3306/test_db"
            jdbc_user => "root"
            parameters => { "city" => "SH" }
            schedule => "* * * * *"
            statement => "SELECT id, name, age, city FROM employee WHERE city = :city"
            use_column_value => true
            tracking_column => "id"
        }
    }
    # The filter part of this file is commented out to indicate that it is
    # optional.
    filter {
        grok {
            match => { "message" => "%{COMBINEDAPACHELOG}"}
        }
        geoip {
            source => "clientip"
        }
    }
    output {
        #stdout { codec => rubydebug }
        elasticsearch {
            hosts => [ "localhost:9200", "localhost:9201", "localhost:9202" ]
        }
        file {
            path => "~/my-logstash.log"
        }
    }

# state

## 状态有关的参数

- record_last_run: boolean(true). 是否要把state存储到配置文件last_run_metadata_path中。
- last_run_metadata_path("/home/ph/.logstash_jdbc_last_run"). 这个文件存储的是sql_last_value的值。
- clean_run: boolean(false). 可以理解为Run Cleanly，即从一个“干净”或全新的条件下运行插件。换句话讲，即是否每次运行后要保留对应的状态信息。在Docs中，描述信息容易产生歧义，需要按照Run Cleanly理解其缺省值false。这个值和record_last_run的作用一样。



- tracking_column: string(""). 待跟踪的列的名称，这个列的值必须有递增的数值。sql_last_value会取这个列的值。
- tracking_column_type: (numeric or timestamp). tracking_column列的数据类型，目前只支持这两种。
- use_column_value: boolean(false). 是否使用一个递增的列的值，而不是时间戳。

待验证：

Employee(name, age, updated_time)
1. tracking_column = "age"




Example: record last run

    input {
        jdbc {
            jdbc_driver_library => "/.../mariadb-java-client-2.1.0.jar"
            jdbc_driver_class => "org.mariadb.jdbc.Driver"
            jdbc_connection_string => "jdbc:mariadb://localhost:3306/test_db"
            jdbc_user => "root"
            #jdbc_password => "123456"
            parameters => { "city" => "SH" }
            schedule => "* * * * *"
            statement => "SELECT id, name, age, city FROM employee WHERE city = :city"

            record_last_run => true
            clean_run => false
            last_run_metadata_path => /home/user/abc

            use_column_value => true
            tracking_column => "id"
            tracking_column_type => "numeric"
            
            
            jdbc_paging_enabled => "true"
            jdbc_page_size => "50000"
        }
    }

