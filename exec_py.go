package main

// http://stackoverflow.com/questions/19397986/calling-python-function-from-go-and-getting-the-function-return-value

import "fmt"
import "os/exec"

func main() {
	cmd := exec.Command("ipython", "-c", "print('foo', 'bar')")
	fmt.Println(cmd.Args)
	out, err := cmd.CombinedOutput()
	// ...
	if err != nil {
		fmt.Println("error occured")
		fmt.Println(err)
	}
	fmt.Println("\nOutput is: ", string(out))
}
