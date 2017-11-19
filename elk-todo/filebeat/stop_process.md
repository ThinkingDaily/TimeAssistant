filebeat - stop & kill

ps -ef 找到sudo启动的pid，比如下面的例子，就是43024

    0 43024 99650   0  1:37下午 ttys009    0:00.01 sudo /.../filebeat -e -c /.../filebeat.yml
    0 43025 43024   0  1:37下午 ttys009    0:00.02 /.../filebeat -e -c /.../filebeat.yml

然后 sudo kill 43024即可。

