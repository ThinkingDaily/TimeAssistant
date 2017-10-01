package main

import (
	"crypto/sha1"
	"fmt"
)

/*
Get the sha1 of file's content.

If success, return the sha1 hex string.
If fail, return "".
*/
func foo(content string) (sum string) {
	data := []byte(content)
	b := sha1.Sum(data)
	return fmt.Sprintf("%x", b)
}

func bar(content string) (sum string) {
	data := []byte(content)

	h := sha1.New()
	h.Write(data)
	b := h.Sum(nil)

	return fmt.Sprintf("%x", b)
}

type ShaFunc func(content string) (sum string)

func main() {
	content := "Hello, Go Programming Language!"

	funcs := []ShaFunc{foo, bar}
	for _, f := range funcs {
		// c6adc2f32ef2455ee0a7f66a874431b20043384f
		fmt.Println("sha1:", f(content))
	}
}
