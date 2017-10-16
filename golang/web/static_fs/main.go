package main 

import (
	"fmt"
	"net/http"
	"encoding/json"
)

type Employee struct {
	Name string 
	Age int 
}

type Response struct {
	Code int `json:"result_code"`
	Message string `json:"message"`
	Data string `json:"data"`
}

func responseFail(w http.ResponseWriter) {
	response(w, 99, "fail response", nil)
}

func responseSuccess(w http.ResponseWriter, data []byte) {
	response(w, 100, "success response", data)
}

func response(w http.ResponseWriter, code int, message string, data []byte) {
	r := Response{code, message, string(data)}
	json_string, err := json.Marshal(r)
	if err != nil {
		fmt.Println("json marshal failed: ", err)
		return 
	}

	fmt.Printf("response: %s\n", json_string)
	w.Write([]byte(json_string))
}

func fooHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Entering Foo handler...")
	e := Employee{"Tom", 10}
	json_string, err := json.Marshal(e)
	if err != nil {
		fmt.Println("Handler failed: ", err)
		responseFail(w)
	} else {
		fmt.Println("Handler success. Json: %s\n", json_string)
		responseSuccess(w, json_string)
	}
}

func main() {
	mux := http.NewServeMux()
	
	indexFS := http.FileServer(http.Dir("./sfs"))
	mux.Handle("/", indexFS)

	mux.HandleFunc("/foo", fooHandler)
	
	http.ListenAndServe(":9999", mux)
}
