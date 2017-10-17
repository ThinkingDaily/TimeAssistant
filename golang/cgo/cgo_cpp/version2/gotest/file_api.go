package main

/*
#cgo CFLAGS: -I../src/file_api/include
#cgo LDFLAGS: -L../bin/libs -lfile_api -lutils -lstdc++
#include <stdlib.h>
#include "file_api.h"
*/
import "C"

//${SRCDIR}

import (
    "unsafe"
    "fmt"
)

const SIZE_DEFAULT int64 = 0

/*
const SIZE_1M int64 = 10485760
const SiZE_1G int64 = 1073741824
*/

func split(filename string) {
    fn := C.CString(filename)
    defer C.free(unsafe.Pointer(fn))

    C.split(fn)
}

func main() {
    fmt.Println("hello")
    split("a/b/c/d.bin")
}