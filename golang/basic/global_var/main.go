package main

import "fmt"

var x int

func print(x int) {
	fmt.Println("x = ", x)
}

func foo() {
	x = 100 // global variable 'x'
}

func bar() {
	x := 200 // local variable 'x'
	print(x)
}

/*
x =  100
x =  200
x =  101
*/
func main() {
	foo()
	print(x)
	x++
	bar()
	print(x)
}
