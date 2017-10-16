package main

import (
    "encoding/json"
    "net/http"
    "log"
)

type Employee struct {
    Name string `json:"name"`
    Age int `json:"age",omitempty`
    Hobby string `json:"hobby",omitempty`
}

type Result struct {
    Code int `json:"code"`
    Message string `json:"message",omitempty`
}

func testHandler(w http.ResponseWriter, req *http.Request) {
    e := &Employee{}
    json.NewDecoder(req.Body).Decode(e)
    log.Println(*e)

    result := Result{Code : 0}
    data, err := json.Marshal(result)
    if err != nil {
        http.Error(w, "Internal Error", http.StatusInternalServerError)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    _, err = w.Write(data)
    if err != nil {
        log.Println(err)
    }
}

func main() {
    mux := http.NewServeMux()
    mux.Handle("/test", http.HandlerFunc(testHandler))

    log.Fatal(http.ListenAndServe("localhost:8000", mux))
}
