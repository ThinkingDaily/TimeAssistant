# Overview
启动容器时，直接运行特定的Python脚本。

# 命令

构建image：

    docker build -t py_ex:v1 .

运行容器：

    docker run -it --rm --name py_ex_inst py_ex:v1
