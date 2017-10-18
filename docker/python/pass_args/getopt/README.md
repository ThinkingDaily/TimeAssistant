# 构建与验证

    docker build -t pass_args:v2 .
    docker run -it --rm --name pass_args_v2 pass_args:v2 python /hello/main.py -a 1234 -b -c -d hello test.txt

# Result

    option a: 1234
    option b
    option c
    option d: hello
    args: ['test.txt']
