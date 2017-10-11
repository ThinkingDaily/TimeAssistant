package main

import (
	"fmt"
	"time"
)

func main() {
	now := time.Now()
	now_string := fmt.Sprintf("%d%02d%02d-%02d%02d%02d-Others",
		now.Year(), now.Month(), now.Day(),
		now.Hour(), now.Minute(), now.Second())
	fmt.Println("Current Time: ", now_string)
}
