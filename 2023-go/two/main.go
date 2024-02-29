package two

import (
	"os"
)

func RunDay(part int, filename string) {
	parts := []func(string){
		RunPartOne,
		RunPartTwo,
	}

	partFunc := parts[part-1]
	bytes, _ := os.ReadFile(filename)
	partFunc(string(bytes))
}
