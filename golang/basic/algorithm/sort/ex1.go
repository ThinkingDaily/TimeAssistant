package main

import (
	"fmt"
	"sort"
)

func main() {
	data := []string{"one", "two", "three", "four"}
	sort.Strings(data)
	fmt.Println(data) //[four one three two]

	sort.Sort(sort.Reverse(sort.StringSlice(data)))
	fmt.Println(data) //[two three one four]
}
