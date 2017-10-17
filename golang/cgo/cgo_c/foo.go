package main 

/*
#cgo LDFLAGS: -L. -lfoo
#include "foo.h"
*/
import "C"

import (
    "fmt"
)

//export go_foo
func go_foo(x int) {
    fmt.Println("foo() in Go, x: ", x)
}

func go_bar() {
    fmt.Println("bar() in Go.")
}

func main() {
    fmt.Println("testing...")

    var x int = 10

    C.c_foo(C.int(x))

    go_bar()
}
