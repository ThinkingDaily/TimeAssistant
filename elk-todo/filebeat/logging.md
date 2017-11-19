# Set up logging

- https://www.elastic.co/guide/en/beats/filebeat/current/configuration-logging.html

## logging configuration

在filebeat.full.yml中，定义了logging的配置项。

    #================================ Logging ======================================
    # There are three options for the log output: syslog, file, stderr.
    # Under Windows systems, the log files are per default sent to the file output,
    # under all other system per default to syslog.

- 日志输出有三种选项： syslog, file, stderr.
- Windows缺省是file，其他系统是syslog

    # Sets log level. The default log level is info.
    # Available log levels are: critical, error, warning, info, debug
    #logging.level: info

- logging.level用于定义输出的日志级别
- 缺省是info
- 一共有5个级别

    # Enable debug output for selected components. To enable all selectors use ["*"]
    # Other available selectors are "beat", "publish", "service"
    # Multiple selectors can be chained.
    #logging.selectors: [ ]

- 定义哪些组件(selector)可用输出debug级别的日志
- ["*"]表示启用所有的selector
- 可用的selector: beat, publish, service
- 可用定义多个selector

    # Send all logging output to syslog. The default is false.
    #logging.to_syslog: true

- 是否将filebeat自身日志发给syslog
- 缺省为false

    # If enabled, filebeat periodically logs its internal metrics that have changed
    # in the last period. For each metric that changed, the delta from the value at
    # the beginning of the period is logged. Also, the total values for
    # all non-zero internal metrics are logged on shutdown. The default is true.
    #logging.metrics.enabled: true

    # The period after which to log the internal metrics. The default is 30s.
    #logging.metrics.period: 30s

- 度量相关

    # Logging to rotating files files. Set logging.to_files to false to disable logging to
    # files.
    logging.to_files: true

- 日志输出到文件

    logging.files:
      # Configure the path where the logs are written. The default is the logs directory
      # under the home path (the binary location).
      #path: /var/log/filebeat

- 日志文件的路径

      # The name of the files where the logs are written to.
      #name: filebeat

- 日志文件的文件名

      # Configure log file size limit. If limit is reached, log file will be
      # automatically rotated
      #rotateeverybytes: 10485760 # = 10MB

- 日志文件size limit

      # Number of rotated log files to keep. Oldest files will be deleted first.
      #keepfiles: 7

- 最多保留的rotated file数目

      # The permissions mask to apply when rotating log files. The default value is 0600.
      # Must be a valid Unix-style file permissions mask expressed in octal notation.
      #permissions: 0600

- 文件权限，缺省0600
