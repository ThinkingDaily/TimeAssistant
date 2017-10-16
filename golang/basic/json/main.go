package main

import (
	"fmt"
	"encoding/json"
)

type Employee struct {
	Name string `json:"name"`
	Age int `json:"age"`
	City string 
}

type Company struct {
    Boss Employee 
    Employees []Employee
}

/*
$ go run json_ex.go 
JSON string:  [123 34 110 97 109 101 34 58 34 84 111 109 34 44 
               34 97 103 101 34 58 51 48 44 34 67 105 116 121 
               34 58 34 66 74 34 125]
JSON string: {"name":"Tom","age":30,"City":"BJ"}
JSON string: [{"name":"Tom","age":30,"City":"BJ"},
              {"name":"Jerry","age":20,"City":"SH"}]
$ 
*/
func foo() {
	tom := Employee{"Tom", 30, "BJ"};
	jerry := Employee{"Jerry", 20, "SH"};

	json_string, err := json.Marshal(tom)
	if err != nil {
		fmt.Println("Error: ", err)
		return 
	}

	fmt.Println("JSON string: ", json_string)
	fmt.Printf("JSON string: %s\n", json_string)

	values := []Employee{tom, jerry}
	json_string, err = json.MarshalIndent(values, "", "    ")
	if err != nil {
		fmt.Println("Error: ", err)
		return 
	}

	fmt.Printf("JSON string: %s\n", json_string)
}

/*
JSON string: 
{
"Boss":{"name":"Cartoon","age":25,"City":"SH"},
"Employees":[
    {"name":"Tom","age":30,"City":"BJ"},
    {"name":"Jerry","age":20,"City":"SH"}
    ]
}
*/
func bar() {
    boss := Employee{"Cartoon", 25, "SH"}
    tom := Employee{"Tom", 30, "BJ"}
    jerry := Employee{"Jerry", 20, "SH"}
    company := Company{}
    company.Boss = boss
    company.Employees = []Employee{tom, jerry}

    json_string, err := json.MarshalIndent(company, "", "    ")
    if err != nil {
        fmt.Println("Error: ", err)
        return 
    }

    fmt.Printf("JSON string: %s\n", json_string)
}

func main() {
	fmt.Println("foo():\n")
    foo()

    fmt.Println("bar():\n")
    bar()
}
