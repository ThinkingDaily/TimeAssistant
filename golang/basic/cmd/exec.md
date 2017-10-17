golang - exec

# Key Points

golang通过exec调用命令行程序。

# test_api.h

#ifndef __TEST_API_H
#define __TEST_API_H

#ifdef __cplusplus
extern "C" {
#endif

void foo(int start, int step, int count);

#ifdef __cplusplus
}
#endif

#endif

# test_api.cpp

#include "test_api.h"

#include <stdio.h>
#include <stdlib.h>

void foo(int start, int step, int count)
{
    int value = start;
    for (int i = 0; i < count; i++) {
        printf("%d\t", value);
        value += step;

        if (value > 5000 && start % 2 == 0) {
            printf("start = %d will exit.\n", start);
            exit(1);
        }
    }
}

# main.cpp

#include <stdlib.h>
#include <stdio.h>

#include "test_api.h"

int main(int argc, const char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s start step max\n", argv[0]);
        return 1;
    }

    int start = atoi(argv[1]);
    int step = atoi(argv[2]);
    int count = atoi(argv[3]);

    foo(start, step, count);
    printf("main exit\n");
    return 0;
}

# main.go

package main

import (
    "sync"
    "fmt"
    "os/exec"
)

func run_cmd(cmd *exec.Cmd) (success bool, output string) {
    out, err := cmd.CombinedOutput()
    if err != nil {
        fmt.Println("error: ", err)
        return false, string(out)
    }

    return true, string(out)
}

type Param struct {
    start int
    step int
    count int
}

func main() {
    wg := sync.WaitGroup{}
    params := []Param{{1, 2, 10000}, {2, 2, 10000}}
    for _, param := range(params) {
        wg.Add(1)
        go func(start, step, count int) {
            defer wg.Done()
            args := []string {fmt.Sprintf("%d", start), fmt.Sprintf("%d", step), fmt.Sprintf("%d", count)}
            cmd := exec.Command("./test", args...)
            fmt.Println("args: ", args)
            success, output := run_cmd(cmd)
            fmt.Printf("output-%d: %s\n", start, output)
            fmt.Printf("success-%d: %t\n", start, success)
        }(param.start, param.step, param.count)
    }

    wg.Wait()
    fmt.Println("main exit")
}
