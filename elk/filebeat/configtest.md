修改得到一个yml配置文件之后，在运行之前，可以用configtest配置项来检查配置文件正确与否。

    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -configtest -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml

结果:

    flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat -e -configtest -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml
    2017/11/20 13:57:31.330933 beat.go:426: INFO Home path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Config path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Data path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/data] Logs path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/logs]
    2017/11/20 13:57:31.331000 metrics.go:23: INFO Metrics logging every 30s
    2017/11/20 13:57:31.331221 beat.go:433: INFO Beat UUID: 517a470d-cd2f-4eb1-a5a4-15110ab099aa
    2017/11/20 13:57:31.331299 beat.go:192: INFO Setup Beat: filebeat; Version: 6.0.0
    2017/11/20 13:57:31.331616 module.go:80: INFO Beat name: flyingbird
    2017/11/20 13:57:31.331861 cfgwarn.go:18: WARN DEPRECATED: -configtest flag has been deprecated, use configtest subcommand Will be removed in version: 6.0
    Config OK
    flying-bird@flyingbird:~$ 

    /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat configtest -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml

根据上面的提示，-configtest选项要被淘汰掉，使用 test config 子命令：

    flying-bird@flyingbird:~$ /home/flying-bird/elk/filebeat-6.0.0-linux-x86/filebeat test config -e -c /home/flying-bird/code_snippets/elk/myconf/filebeat/filebeat_01.yml
    2017/11/20 14:04:11.430049 beat.go:426: INFO Home path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Config path: [/home/flying-bird/elk/filebeat-6.0.0-linux-x86] Data path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/data] Logs path: [/home/flying-bird/code_snippets/elk/myconf/filebeat/logs]
    2017/11/20 14:04:11.430337 beat.go:433: INFO Beat UUID: 517a470d-cd2f-4eb1-a5a4-15110ab099aa
    2017/11/20 14:04:11.430430 beat.go:192: INFO Setup Beat: filebeat; Version: 6.0.0
    2017/11/20 14:04:11.430516 metrics.go:23: INFO Metrics logging every 30s
    2017/11/20 14:04:11.430840 module.go:80: INFO Beat name: flyingbird
    Config OK
    flying-bird@flyingbird:~$ 

详细情况参考configtest_subcommand.log。

