package main

import (
	"fmt"
	"os"
	"time"
)

func Forever() {
	for i := 0; ; i++ {
		fmt.Println(i)
	}
}

func Wait(f func(), t time.Duration) {
	id := make(chan int)
	ok := make(chan int)

	go func() {
		id <- os.Getpid()
		f()
		ok <- 1
	}()

	proc := os.Process{Pid: <-id}
	select {
	case <-time.After(t):
		proc.Kill()
	case <-ok:
		//
	}
}

func main() {
	Wait(Forever(), time.Second*5)
	fmt.Println("over")
}
