# ./filebeat --help

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat --help
  Usage:
    filebeat [flags]
    filebeat [command]

  Available Commands:
    export      Export current config or index template
    help        Help about any command
    modules     Manage configured modules
    run         Run filebeat
    setup       Setup index template, dashboards and ML jobs
    test        Test config
    version     Show current version info

  Flags:
    -E, --E Flag                      Configuration overwrite (default null)
    -M, --M Flag                      Module configuration overwrite (default null)
    -N, --N                           Disable actual publishing for testing
    -c, --c argList                   Configuration file, relative to path.config (default beat.yml)
        --cpuprofile string           Write cpu profile to file
    -d, --d string                    Enable certain debug selectors
    -e, --e                           Log to stderr and disable syslog/file output
    -h, --help                        help for filebeat
        --httpprof string             Start pprof http server
        --memprofile string           Write memory profile to this file
        --modules string              List of enabled modules (comma separated)
        --once                        Run filebeat only once until all harvesters reach EOF
        --path.config flagOverwrite   Configuration path
        --path.data flagOverwrite     Data path
        --path.home flagOverwrite     Home path
        --path.logs flagOverwrite     Logs path
        --plugin pluginList           Load additional plugins
        --setup                       Load the sample Kibana dashboards
        --strict.perms                Strict permission checking on config files (default true)
    -v, --v                           Log at INFO level

  Use "filebeat [command] --help" for more information about a command.

# ./filebeat configtest --help (ERROR)

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat configtest --help
  Error: unknown command "configtest" for "filebeat"
  Run 'filebeat --help' for usage.

# ./filebeat run --help

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat run --help
  Run filebeat

  Usage:
    filebeat run [flags]

  Flags:
    -N, --N                   Disable actual publishing for testing
        --cpuprofile string   Write cpu profile to file
    -h, --help                help for run
        --httpprof string     Start pprof http server
        --memprofile string   Write memory profile to this file
        --modules string      List of enabled modules (comma separated)
        --once                Run filebeat only once until all harvesters reach EOF
        --setup               Load the sample Kibana dashboards

  Global Flags:
    -E, --E Flag                      Configuration overwrite (default null)
    -M, --M Flag                      Module configuration overwrite (default null)
    -c, --c argList                   Configuration file, relative to path.config (default beat.yml)
    -d, --d string                    Enable certain debug selectors
    -e, --e                           Log to stderr and disable syslog/file output
        --path.config flagOverwrite   Configuration path
        --path.data flagOverwrite     Data path
        --path.home flagOverwrite     Home path
        --path.logs flagOverwrite     Logs path
        --plugin pluginList           Load additional plugins
        --strict.perms                Strict permission checking on config files (default true)
    -v, --v                           Log at INFO level
  flying-bird@flyingbird:~$ 

# ./filebeat test --help

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat test --help
  Test config

  Usage:
    filebeat test [command]

  Available Commands:
    config      Test configuration settings
    output      Test filebeat can connect to the output by using the current settings

  Flags:
    -h, --help             help for test
        --modules string   List of enabled modules (comma separated)

  Global Flags:
    -E, --E Flag                      Configuration overwrite (default null)
    -M, --M Flag                      Module configuration overwrite (default null)
    -c, --c argList                   Configuration file, relative to path.config (default beat.yml)
    -d, --d string                    Enable certain debug selectors
    -e, --e                           Log to stderr and disable syslog/file output
        --path.config flagOverwrite   Configuration path
        --path.data flagOverwrite     Data path
        --path.home flagOverwrite     Home path
        --path.logs flagOverwrite     Logs path
        --plugin pluginList           Load additional plugins
        --strict.perms                Strict permission checking on config files (default true)
    -v, --v                           Log at INFO level

  Use "filebeat test [command] --help" for more information about a command.

# ./filebeat test config --help

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat test config --help
  Test configuration settings

  Usage:
    filebeat test config [flags]

  Flags:
    -h, --help   help for config

  Global Flags:
    -E, --E Flag                      Configuration overwrite (default null)
    -M, --M Flag                      Module configuration overwrite (default null)
    -c, --c argList                   Configuration file, relative to path.config (default beat.yml)
    -d, --d string                    Enable certain debug selectors
    -e, --e                           Log to stderr and disable syslog/file output
        --path.config flagOverwrite   Configuration path
        --path.data flagOverwrite     Data path
        --path.home flagOverwrite     Home path
        --path.logs flagOverwrite     Logs path
        --plugin pluginList           Load additional plugins
        --strict.perms                Strict permission checking on config files (default true)
    -v, --v                           Log at INFO level

# ./filebeat test config -e -c filebeat.yml

  flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat test config -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml
  2017/11/20 14:04:11.430049 beat.go:426: INFO Home path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Config path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Data path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/data] Logs path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/logs]
  2017/11/20 14:04:11.430337 beat.go:433: INFO Beat UUID: 517a470d-cd2f-4eb1-a5a4-15110ab099aa
  2017/11/20 14:04:11.430430 beat.go:192: INFO Setup Beat: filebeat; Version: 6.0.0
  2017/11/20 14:04:11.430516 metrics.go:23: INFO Metrics logging every 30s
  2017/11/20 14:04:11.430840 module.go:80: INFO Beat name: flyingbird
  Config OK
  flying-bird@flyingbird:~$ 
