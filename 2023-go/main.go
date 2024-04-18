package main

import (
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"

	"2023-go/one"
	"2023-go/two"
	"2023-go/three"
	"2023-go/four"
	"2023-go/five"
	"2023-go/six"
	"2023-go/seven"
	"2023-go/eight"
)

type day struct {
	folder   string
	runnable func(int, string)
}

func main() {
	days := []day{
		{"one", one.RunDay},
		{"two", two.RunDay},
		{"three", three.RunDay},
		{"four", four.RunDay},
		{"five", five.RunDay},
		{"six", six.RunDay},
		{"seven", seven.RunDay},
		{"eight", eight.RunDay},
	}

	day, part, file := parseArgs()

	if day > len(days) || day < 1 {
		fmt.Println("usage: go run main.go <day.part> <input>")
		fmt.Printf("  <day> must be between 1 and %d inclusive\n", len(days))

		os.Exit(0)
	}

	if part > 2 || part < 1 {
		fmt.Println("usage: go run main.go <day.part> <input>")
		fmt.Println("  <part> must be either 1 or 2")

		os.Exit(0)
	}

	dayObj := days[day-1]
	filename := fmt.Sprintf("%s/%s.txt", dayObj.folder, file)
	dayObj.runnable(part, filename)
}

func parseArgs() (int, int, string) {
	args := strings.Join(os.Args, " ")

	pattern := regexp.MustCompile(`.* (\d)\.([12]) (.*)`)

	matches := pattern.FindStringSubmatch(args)
	if matches == nil {
		fmt.Println("usage: go run main.go <day.part> <input>")
		fmt.Println("  <day> must be an integer")
		fmt.Println("  <part> must be 1 or 2")
		fmt.Println("  <input> must be a filename")

		os.Exit(0)
	}

	day, _ := strconv.Atoi(matches[1])
	part, _ := strconv.Atoi(matches[2])

	return day, part, matches[3]
}
