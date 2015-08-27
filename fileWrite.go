package main
// ref   https://gobyexample.com/writing-files

import (
	"fmt"
	"os"
	"strconv"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	var f *os.File
	var err error
	var n1, n2, n3 int
	var n int64

	d1 := []byte("hello\ngo\n")
	d2 := []byte{115, 111, 109, 101, 10}

	f, err = os.Create("./data.txt")
	check(err)
	defer f.Close()

	n1, err = f.WriteString("writes\n")
	fmt.Printf("wrote %d bytes\n", n1)
	n2, err = f.Write(d1)
	fmt.Printf("wrote %d bytes\n", n2)
	n3, err = f.Write(d2)
	fmt.Printf("wrote %d bytes\n", n3)
	n = int64(n1 + n2 + n3)
	_, err = f.Write([]byte(strconv.FormatInt(n, 10)))

	f.Sync()
}
