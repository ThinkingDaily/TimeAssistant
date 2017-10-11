package main

import "fmt"

type Student struct {
	name string
	age  int
}

type People struct {
	Student
}

func (people *People) Print() {
	fmt.Printf("People[name:%s, age:%d]\n", people.name, people.age)
}

func PrintStudent(student *Student) {
	fmt.Printf("Student[name:%s, age:%d]\n", student.name, student.age)
}

/*
People[name:Tom, age:3]
People[name:Jerry, age:5]
Student[name:Tom, age:3]
People[name:Tom, age:4]
Student[name:Tom, age:3]
*/
func main() {
	people := People{}
	people.name = "Tom"
	people.age = 3

	people2 := People{Student{name: "Jerry", age: 5}}

	people.Print()
	people2.Print()

	var student Student
	student = people.Student
	PrintStudent(&student)

	var people3 People = People{student}
	people3.age++
	people3.Print()
	PrintStudent(&student)
}
