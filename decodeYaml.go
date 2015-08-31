package main

import (
	"fmt"
	"gopkg.in/yaml.v2"
	"io/ioutil"
	"time"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func DecodeYamlFile(mm map[interface{}]interface{}) map[interface{}]interface{} {
	data, err := ioutil.ReadFile("config.yaml")
	if err != nil {
		return mm // check(err) not used...
	}
	fmt.Println("YAML file opened.") // update m everytime the file is updated
	m := make(map[interface{}]interface{})
	err = yaml.Unmarshal([]byte(data), &m)
	return m
}

func main() {
	var m map[interface{}]interface{}
	for i := 0; i < 100; i++ {
		m = DecodeYamlFile(m)
		fmt.Println(i, " :: ", m)
		fmt.Println("Name: ", m["name"])
		fmt.Println("Age : ", m["age"])
		fmt.Println("Tax : ", m["tax"])
		t := m["salary"].(float64) // type assertion
		fmt.Println("Salary", t)

		time.Sleep(300 * time.Millisecond)
	}
}

// config.yaml:vvv
// name: John Smith
// gender: male
// married: true
// age: 37
// salary: 6800.0
// tax: 5.8
