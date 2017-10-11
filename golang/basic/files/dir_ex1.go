package main

import (
	"fmt"
	"os"
)

func IsDir(name string) bool {
	fi, err := os.Stat(name)
	if err != nil {
		fmt.Println("Error: ", err)
		return false
	}

	return fi.IsDir()
}

func CreateDir(name string) bool {
	if IsDir(name) {
		fmt.Printf("%s is already a directory.\n", name)
		return true
	}

	if createDirImpl(name) {
		fmt.Println("Create directory successfully.")
		return true
	} else {
		return false
	}
}

func createDirImpl(name string) bool {
	err := os.MkdirAll(name, 0666)
	if err == nil {
		return true
	} else {
		fmt.Println("Error: ", err)
		return false
	}
}

/*


Error:  GetFileAttributesEx ./a/b/c: The system cannot find the path specified.
Create directory successfully.
./a/b/c is already a directory.
*/
func main() {
	name := "./a/b/c"
	CreateDir(name)
	CreateDir(name)
}
