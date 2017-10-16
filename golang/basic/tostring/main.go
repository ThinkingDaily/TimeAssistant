package main

import (
	"fmt"
)

type Employee struct {
	Name string
	City string
}

func (e *Employee) String() string {
	return fmt.Sprintf("Employee[Name: %s, City: %s]", e.Name, e.City)
}

func main() {
	employee := Employee{Name: "Tom", City: "Shanghai"}
	fmt.Println(employee)
	fmt.Println(employee.String())
	fmt.Printf("%s\n", employee)
}
