package main

import "fmt"

func main() {
	values := make(map[int]string)
	values[1] = "One"
	values[2] = "two"
	values[3] = "three"

	//values: map[1:One 2:two 3:three]
	fmt.Println("values:", values)

	delete(values, 2)

	//values: map[1:One 3:three]
	fmt.Println("values:", values)

	value, found := values[2]

	//value:  , found: false
	fmt.Println("value:", value, ", found:", found)
}
