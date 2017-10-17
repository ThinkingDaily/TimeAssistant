package main 

/*
#cgo LDFLAGS: -L. -ltest -lstdc++
#include "test_api.h"
*/
import "C"

import (
    //"fmt"
)

func main() {
    var x int = 100

    C.myprint(C.int(x))
}