package three

import (
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func RunDay(filename string, part string) {
	var file, _ = os.ReadFile("three/" + filename + ".txt")
	var lines = strings.Split(string(file), "\n")

	var parts = make(map[string]func(lines []string))
	parts["one"] = partTwo
	parts["two"] = partTwo

	parts[part](lines)
}

func parseLine(line string) (int, int, int, int, int) {
	var pattern = regexp.MustCompile("^#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)$")
	var matches = pattern.FindStringSubmatch(line)

	var id, _ = strconv.Atoi(matches[1])
	var left, _ = strconv.Atoi(matches[2])
	var top, _ = strconv.Atoi(matches[3])
	var width, _ = strconv.Atoi(matches[4])
	var height, _ = strconv.Atoi(matches[5])

	return id, left, top, width, height
}

func partTwo(lines []string) {
	var grid = make(map[string]int)
	var intact = make([]bool, 1500)

	for _, line := range lines {
		var id, left, top, width, height = parseLine(line)
		intact[id] = true

		for x := left; x < left+width; x++ {
			for y := top; y < top+height; y++ {
				var key = fmt.Sprintf("%d,%d", x, y)
				var val, hasVal = grid[key]

				if hasVal {
					intact[id] = false

					if val != -1 {
						intact[val] = false
						grid[key] = -1
					}
				} else {
					grid[key] = id
				}
			}
		}
	}

	var count = 0
	for _, value := range grid {
		if value < 0 {
			count++
		}
	}

	for index, value := range intact {
		if value {
			fmt.Printf("winner: %d\n", index)
		}
	}

	fmt.Printf("total collisions: %d\n", count)
}
