logstash - options



# help

命令：

    ./bin/logstash --help

# version 

查询版本：

    ./bin/logstash --version

# log format

    --log.format FORMAT : default is plain

# -e

The -e flag enables you to specify a configuration directly from the command line. Specifying configurations at the command line lets you quickly test configurations without having to edit a file between iterations. The pipeline in the example takes input from the standard input, stdin, and moves that input to the standard output, stdout, in a structured format.

不需要创建一个配置文件，而直接从命令行获取pipeline配置参数。

示例：

    -e 'input { stdin { } } output { stdout {} }'

含义：从标准输入获得输入数据；并将输入的值扔给stdout（以结构化-json的形式）。


## -e缺省值

help中的说明：

    "input { stdin { type => stdin } }"
    and if no output is specified, then the
    following is used as the default output:
    "output { stdout { codec => rubydebug } }"
    If you wish to use both defaults, please use
    the empty string for the '-e' flag.
    (default: nil)

即缺省值为："input { stdin { type => stdin } } output { stdout { codec => rubydebug } }"

# Command Example

    ./bin/logstash -e 'input { stdin { } } output { stdout {} }'

    ./bin/logstash --path.data fota_logstash/data --path.logs fota_logstash/logs -e 'input { stdin { } } output { stdout {} }'

# Appendix - help content

    $ ./bin/logstash --help
    ERROR StatusLogger No log4j2 configuration file found. Using default configuration: logging only errors to the console.
    Usage:
        bin/logstash [OPTIONS]

    Options:
        -n, --node.name NAME          Specify the name of this logstash instance, if no value is given
                                      it will default to the current hostname.
                                       (default: "hostname")
        -f, --path.config CONFIG_PATH Load the logstash config from a specific file
                                      or directory.  If a directory is given, all
                                      files in that directory will be concatenated
                                      in lexicographical order and then parsed as a
                                      single config file. You can also specify
                                      wildcards (globs) and any matched files will
                                      be loaded in the order described above.
        -e, --config.string CONFIG_STRING Use the given string as the configuration
                                      data. Same syntax as the config file. If no
                                      input is specified, then the following is
                                      used as the default input:
                                      "input { stdin { type => stdin } }"
                                      and if no output is specified, then the
                                      following is used as the default output:
                                      "output { stdout { codec => rubydebug } }"
                                      If you wish to use both defaults, please use
                                      the empty string for the '-e' flag.
                                       (default: nil)
        fd

        --modules MODULES             Load Logstash modules.
                                      Modules can be defined using multiple instances
                                      '--modules module1 --modules module2',
                                         or comma-separated syntax
                                      '--modules=module1,module2'
                                      Cannot be used in conjunction with '-e' or '-f'
                                      Use of '--modules' will override modules declared
                                      in the 'logstash.yml' file.
        -M, --modules.variable MODULES_VARIABLE Load variables for module template.
                                      Multiple instances of '-M' or
                                      '--modules.variable' are supported.
                                      Ignored if '--modules' flag is not used.
                                      Should be in the format of
                                      '-M "MODULE_NAME.var.PLUGIN_TYPE.PLUGIN_NAME.VARIABLE_NAME=VALUE"'
                                      as in
                                      '-M "example.var.filter.mutate.fieldname=fieldvalue"'
        -w, --pipeline.workers COUNT  Sets the number of pipeline workers to run.
                                       (default: 8)
        -b, --pipeline.batch.size SIZE Size of batches the pipeline is to work in.
                                       (default: 125)
        -u, --pipeline.batch.delay DELAY_IN_MS When creating pipeline batches, how long to wait while polling
                                      for the next event.
                                       (default: 5)
        --pipeline.unsafe_shutdown    Force logstash to exit during shutdown even
                                      if there are still inflight events in memory.
                                      By default, logstash will refuse to quit until all
                                      received events have been pushed to the outputs.
                                       (default: false)
        --path.data PATH              This should point to a writable directory. Logstash
                                      will use this directory whenever it needs to store
                                      data. Plugins will also have access to this path.
                                       (default: "/your_dir/logstash-5.5.2/data")
        -p, --path.plugins PATH       A path of where to find plugins. This flag
                                      can be given multiple times to include
                                      multiple paths. Plugins are expected to be
                                      in a specific directory hierarchy:
                                      'PATH/logstash/TYPE/NAME.rb' where TYPE is
                                      'inputs' 'filters', 'outputs' or 'codecs'
                                      and NAME is the name of the plugin.
                                       (default: [])
        -l, --path.logs PATH          Write logstash internal logs to the given
                                      file. Without this flag, logstash will emit
                                      logs to standard output.
                                       (default: "/your_dir/logstash-5.5.2/logs")
        --log.level LEVEL             Set the log level for logstash. Possible values are:
                                        - fatal
                                        - error
                                        - warn
                                        - info
                                        - debug
                                        - trace
                                       (default: "info")
        --config.debug                Print the compiled config ruby code out as a debug log (you must also have --log.level=debug enabled).
                                      WARNING: This will include any 'password' options passed to plugin configs as plaintext, and may result
                                      in plaintext passwords appearing in your logs!
                                       (default: false)
        -i, --interactive SHELL       Drop to shell instead of running as normal.
                                      Valid shells are "irb" and "pry"
        -V, --version                 Emit the version of logstash and its friends,
                                      then exit.
        -t, --config.test_and_exit    Check configuration for valid syntax and then exit.
                                       (default: false)
        -r, --config.reload.automatic Monitor configuration changes and reload
                                      whenever it is changed.
                                      NOTE: use SIGHUP to manually reload the config
                                       (default: false)
        --config.reload.interval RELOAD_INTERVAL How frequently to poll the configuration location
                                      for changes, in seconds.
                                       (default: 3)
        --http.host HTTP_HOST         Web API binding host (default: "127.0.0.1")
        --http.port HTTP_PORT         Web API http port (default: 9600..9700)
        --log.format FORMAT           Specify if Logstash should write its own logs in JSON form (one
                                      event per line) or in plain text (using Ruby's Object#inspect)
                                       (default: "plain")
        --path.settings SETTINGS_DIR  Directory containing logstash.yml file. This can also be
                                      set through the LS_SETTINGS_DIR environment variable.
                                       (default: "/your_dir/logstash-5.5.2/config")
        --verbose                     Set the log level to info.
                                      DEPRECATED: use --log.level=info instead.
        --debug                       Set the log level to debug.
                                      DEPRECATED: use --log.level=debug instead.
        --quiet                       Set the log level to info.
                                      DEPRECATED: use --log.level=quiet instead.
        -h, --help                    print help
    $ 


