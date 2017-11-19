Kibana-运行

# 运行

在配置好数据之后，第一次运行时，不用在后台运行，这样便于发现问题。

-h 选项可以显示所有命令参数。

    $ ./bin/kibana
    [plugin:kibana@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:elasticsearch@5.5.2] Status changed from uninitialized to yellow - Waiting for Elasticsearch
    [plugin:console@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:metrics@5.5.2] Status changed from uninitialized to green - Ready
    [plugin:timelion@5.5.2] Status changed from uninitialized to green - Ready
    [listening] Server running at http://localhost:5601
    [ui settings] Status changed from uninitialized to yellow - Elasticsearch plugin is yellow
    [plugin:elasticsearch@5.5.2] Status changed from yellow to green - Kibana index ready
    [ui settings] Status changed from yellow to green - Ready
     
验证可以正常运行之后，可以Ctrl+C，然后再以 './bin/kibana &' 方式运行。

# kibana

bin/kibana是一个shell脚本:

    #!/bin/sh
    SCRIPT=$0

    # SCRIPT may be an arbitrarily deep series of symlinks. Loop until we have the concrete path.
    while [ -h "$SCRIPT" ] ; do
      ls=$(ls -ld "$SCRIPT")
      # Drop everything prior to ->
      link=$(expr "$ls" : '.*-> \(.*\)$')
      if expr "$link" : '/.*' > /dev/null; then
        SCRIPT="$link"
      else
        SCRIPT=$(dirname "$SCRIPT")/"$link"
      fi
    done

    DIR="$(dirname "${SCRIPT}")/.."
    NODE="${DIR}/node/bin/node"
    test -x "$NODE" || NODE=$(which node)
    if [ ! -x "$NODE" ]; then
      echo "unable to find usable node.js executable."
      exit 1
    fi

    exec "${NODE}" $NODE_OPTIONS --no-warnings "${DIR}/src/cli" ${@}

# pid

结合上面的shell脚本，kibana运行后，对应的命令是：

    ./bin/../node/bin/node --no-warnings ./bin/../src/cli

Detail:

    $ ps
      PID TTY           TIME CMD
    89454 ttys000    0:00.02 -bash
    89466 ttys001    0:00.03 -bash
    90841 ttys001    0:04.25 ./bin/../node/bin/node --no-warnings ./bin/../src/cli
    89475 ttys002    0:00.01 -bash
    89494 ttys003    0:00.01 -bash
    89506 ttys004    0:00.03 -bash
    89533 ttys007    0:00.03 -bash
    89549 ttys008    0:00.03 -bash
    $ ls -l node/bin/node 
    -rwxr-xr-x@ 1 user group  30154480  8 14 20:44 node/bin/node
    $ ls -l src/cli
    total 56
    -rw-r--r--@ 1 user group  1466  8 14 20:44 cli.js
    -rw-r--r--@ 1 user group   583  8 14 20:44 color.js
    -rw-r--r--@ 1 user group  2589  8 14 20:44 command.js
    -rw-r--r--@ 1 user group   415  8 14 20:44 dev_ssl.js
    -rw-r--r--@ 1 user group  1840  8 14 20:44 help.js
    -rw-r--r--@ 1 user group    72  8 14 20:44 index.js
    -rw-r--r--@ 1 user group   835  8 14 20:44 log.js
    drwxr-xr-x@ 4 user group   136  8 14 20:44 serve
    $ 

据此找到pid之后，可以kill。
