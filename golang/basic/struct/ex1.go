package main

import "fmt"
import "encoding/json"

type Point struct {
	X, Y int
}

type Circle struct {
	Center Point
	Radius int
}

type Wheel struct {
	Circle Circle
	Spokes int
}

func foo() {
	var w Wheel
	w.Circle.Center.X = 8
	w.Circle.Center.Y = 8
	w.Circle.Radius = 5
	w.Spokes = 20

	fmt.Println("foo(): ", w)
}

type Circle2 struct {
	Point  // anonymous fields with a named type
	Radius int
}

type Wheel2 struct {
	Circle2
	Spokes int
}

func bar() {
	var w Wheel2
	w.X = 18
	w.Y = 18
	w.Radius = 15
	w.Spokes = 120

	fmt.Println("bar(): ", w)
}

type Wheel3 struct {
	*Point
	Radius int
}

func baz() {
	var w Wheel3
	w = Wheel3{&Point{28, 28}, 25}

	json_string, err := json.Marshal(w)
	if err != nil {
		fmt.Println("Error: ", err)
	} else {
		fmt.Printf("baz(): %s\n", json_string)
	}

	fmt.Printf("baz(): %#v\n", w)

}

/*
foo():  {{{8 8} 5} 20}
bar():  {{{18 18} 15} 120}
baz(): {"X":28,"Y":28,"Radius":25}
baz(): main.Wheel3{Point:(*main.Point)(0xc04200a340), Radius:25}
*/
func main() {
	foo()
	bar()
	baz()
}
