# Overview

验证docker调用shell脚本的功能。——shell脚本又调用python脚本。

# 构建&验证

    docker build -t shell_ex:v1 .
    docker run -it --rm --name shell_ex_v1 shell_ex:v1
