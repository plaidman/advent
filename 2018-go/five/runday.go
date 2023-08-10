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
	parts["two"] = partTwo

	parts[part](runes)
}

func printPoly(poly *Unit) {
	current := poly
	for current != nil {
		fmt.Print(current.letter())
		current = current.nextUnit
	}

	fmt.Println()
}

func buildPoly(runes []rune, omit rune) (*Unit, int) {
	first := NewUnit(' ')
	current := first
	length := 0

	for i := 0; i < len(runes); i++ {
		if runes[i] == omit || runes[i]-32 == omit {
			continue
		}

		next := NewUnit(runes[i])
		next.insertAfter(current)
		length++
		current = next
	}

	return first.nextUnit, length
}

func partOne(runes []rune) {
	poly, length := buildPoly(runes, ' ')

	current := poly
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

func partTwo(runes []rune) {
	lowest := 20000

	for i := 'A'; i <= 'Z'; i++ {
		poly, length := buildPoly(runes, i)

		current := poly
		for current.nextUnit != nil {
			if current.clashesWithNext() {
				current = current.destroyPair()
				length -= 2
			} else {
				current = current.nextUnit
			}
		}

		if length < lowest {
			lowest = length
		}
		fmt.Printf("%c: %d\n", i, length)
	}

	fmt.Println(lowest)
}
