package five

import (
	"fmt"
	"os"
)

func RunDay(filename string, part string) {
	file, _ := os.ReadFile("five/" + filename + ".txt")
	runes := []rune(string(file))

	parts := make(map[string]func(lines []rune))
	parts["one"] = partOne
	parts["two"] = partOne

	parts[part](runes)
}

func buildPoly(runes []rune) *Unit {
	first := NewUnit(runes[0])
	current := first

	for i := 1; i < len(runes); i++ {
		next := NewUnit(runes[i])
		next.insertAfter(current)
		current = next
	}

	return first
}

func partOne(runes []rune) {
	poly := buildPoly(runes)

	current := poly
	length := len(runes)
	for current.nextUnit != nil {
		if current.clashesWithNext() {
			current = current.destroyPair()
			length -= 2
		} else {
			current = current.nextUnit
		}
	}

	fmt.Println(length)
}
