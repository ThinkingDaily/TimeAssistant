package main

import (
	"fmt"
	"os/exec"
)

func run_cmd(cmd *exec.Cmd) {
	out, err := cmd.Output() //CombinedOutput()
	if err != nil {
		fmt.Println("Error: ", err)
		return
	}

	fmt.Println(string(out))
}

func main() {
	cmd := exec.Command("help")
	run_cmd(cmd)

	cmd = exec.Command("dir", "d:/examples")
	run_cmd(cmd)
}
