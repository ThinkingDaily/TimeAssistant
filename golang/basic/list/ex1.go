package main

import (
	"container/list"
	"fmt"
)

/*
0       1       2       3       4       5
*/
func main() {
	var x list.List // or x := list.New()
	e1 := x.PushBack(1)
	x.PushBack(3)
	e5 := x.PushBack(5)
	x.PushFront(0)
	x.InsertAfter(2, e1)
	x.InsertBefore(4, e5)

	for e := x.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value.(int), "\t")
	}

	fmt.Println()
}
