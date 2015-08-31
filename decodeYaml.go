package main

import (
	"fmt"
	"gopkg.in/yaml.v2"
	"io/ioutil"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func DecodeYamlFile() map[interface{}]interface{} {
	data, err := ioutil.ReadFile("config.yaml")
	check(err)
	fmt.Println("YAML file opened.")
	m := make(map[interface{}]interface{})
	err = yaml.Unmarshal([]byte(data), &m)
	return m
}

func main() {
	m := DecodeYamlFile()
	fmt.Println(m)
	fmt.Println("Name: ", m["name"])
	fmt.Println("Age : ", m["age"])
	fmt.Println("Tax : ", m["tax"])
}

// config.yaml:vvv
// name: John Smith
// gender: male
// married: true
// age: 37
// salary: 6800.0
// tax: 58.0
