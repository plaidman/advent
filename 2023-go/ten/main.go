package ten

import (
	"bufio"
	"fmt"
	"os"
)

func RunDay(part int, filename string) {
	field := NewField()

	file, _ := os.Open(filename)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		field.AddLine(line)
	}

	pawns := field.FindTravelers()
	midpoint := field.FindMidpoint(pawns)

	fmt.Println("midpoint", midpoint)
}
