# Overview

在6.0之前的版本中，yml配置文件中有一个名为document_type的配置项。

document\_type对应的是Elasticsearch的type。对于log prospector，缺省是log。在6.0版本中，可以添加该选项，参考filebeat_02.xml，但运行发现该配置不起任何作用。用test config也不会报任何错误。

    #------------------------------ Log prospector --------------------------------
    - type: log

      # Change to true to enable this prospector configuration.
      enabled: true

      # Paths that should be crawled and fetched. Glob based paths.
      # To fetch all ".log" files from a specific level of subdirectories
      # /var/log/*/*.log can be used.
      # For each file found under this path, a harvester is started.
      # Make sure not file is defined twice as this can lead to unexpected behaviour.
      paths:
        - /home/flying-bird/code_snippets/elk/myconf/filebeat/input_logs/*.log
        #- c:\programdata\elasticsearch\logs\*

      # 
      # Type to be published in the 'type' field. For Elasticsearch output,
      # the type defines the document type these entries should be stored
      # in. Default: log
      document_type: foo_app


# 运行

    rm ~/code_snippets/elk/myconf/filebeat/data/registry
    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_02.yml
    
# 结论

6.0及后续版本不需考虑document_type配置。
