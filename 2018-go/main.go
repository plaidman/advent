package main

import (
	"advent/2018/four"
	"advent/2018/one"
	"advent/2018/three"
	"advent/2018/two"
	"os"
)

func main() {
	if len(os.Args) != 4 {
		panic("arguments: [day] [file] [part]")
	}

	var days = make(map[string]func(filename string, part string), 50)
	days["one"] = one.RunDay
	days["two"] = two.RunDay
	days["three"] = three.RunDay
	days["four"] = four.RunDay

	days[os.Args[1]](os.Args[2], os.Args[3])
}
