package main

import (
	"fmt"
)

func square(n int) int {
	return n * n
}

func cube(n int) int {
	return n * n * n
}

type transformx func(n int) (result int)

func main() {
	funcs := []transformx{square, cube}

	for i := 0; i < 5; i++ {
		fmt.Print(i)
		for _, f := range funcs {
			fmt.Print(" --> ", f(i))
		}
		fmt.Println()
	}
}