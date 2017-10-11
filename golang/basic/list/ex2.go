package main

import (
	"container/list"
	"encoding/json"
	"fmt"
)

type Employee struct {
	Name string
	City string
}

func (e *Employee) String() string {
	return fmt.Sprintf("Employee[address: %p, Name: %s, City: %s]", e, e.Name, e.City)
}

func foo() {
	employees := list.New()
	for i := 1; i <= 5; i++ {
		employees.PushBack(&Employee{fmt.Sprintf("name%d", i), fmt.Sprintf("city%d", i)})
	}

	for e := employees.Front(); e != nil; e = e.Next() {
		fmt.Println(e)
	}

	json_string, err := json.Marshal(employees)
	if err != nil {
		fmt.Println("JSON failed: ", err)
	} else {
		fmt.Printf("JSON: %s\n", json_string)
	}

	json_string, err = json.Marshal(employees.Front().Value)
	if err != nil {
		fmt.Println("JSON failed: ", err)
	} else {
		fmt.Printf("JSON: %s\n", json_string)
	}

	var sliceEmployees []*Employee
	list2slice(employees, &sliceEmployees)
	json_string, err = json.Marshal(sliceEmployees)

	if err != nil {
		fmt.Println("JSON failed: ", err)
	} else {
		fmt.Printf("JSON: %s\n", json_string)
	}
}

func list2slice(listEmployees *list.List, sliceEmployees *[]*Employee) {
	*sliceEmployees = make([]*Employee, 0, listEmployees.Len())
	for e := listEmployees.Front(); e != nil; e = e.Next() {
		if employee, ok := e.Value.(*Employee); ok {
			*sliceEmployees = append(*sliceEmployees, employee)
		} else {
			fmt.Println("Type cast error.")
		}
	}
}

/*
&{0xc042050180 0xc042050120 0xc042050120 Employee[address: 0xc042004660, Name: name1, City: city1]}
&{0xc0420501b0 0xc042050150 0xc042050120 Employee[address: 0xc042004680, Name: name2, City: city2]}
&{0xc0420501e0 0xc042050180 0xc042050120 Employee[address: 0xc0420046a0, Name: name3, City: city3]}
&{0xc042050210 0xc0420501b0 0xc042050120 Employee[address: 0xc0420046c0, Name: name4, City: city4]}
&{0xc042050120 0xc0420501e0 0xc042050120 Employee[address: 0xc0420046e0, Name: name5, City: city5]}
JSON: {}
JSON: {"Name":"name1","City":"city1"}
JSON: [{"Name":"name1","City":"city1"},
       {"Name":"name2","City":"city2"},
       {"Name":"name3","City":"city3"},
       {"Name":"name4","City":"city4"},
       {"Name":"name5","City":"city5"}]
*/
func main() {
	foo()
}
