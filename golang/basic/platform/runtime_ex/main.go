package main

import (
    "runtime"
    "fmt"
)

/*
case 1:
    arch: amd64
    os: darwin

case 2:
    arch: amd64
    os: linux

case 3:
	arch: 386
    os: linux
 */
func main() {
    fmt.Println("arch:", runtime.GOARCH)
    fmt.Println("os:", runtime.GOOS)
}