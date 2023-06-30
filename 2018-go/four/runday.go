package four

import (
	"fmt"
	"os"
	"strings"
)

func RunDay(filename string, part string) {
	file, _ := os.ReadFile("four/" + filename + ".txt")
	lines := strings.Split(string(file), "\n")

	parts := make(map[string]func(lines []string))
	parts["one"] = partOne
	parts["two"] = partTwo

	parts[part](lines)
}

func partOne(lines []string) {
	events := CreateEventList(lines)
	guards := CreateGuardList(events)

	sleepiestGuard := guards.FindSleepiestGuard()
	sleepiestGuard.printGuard()

	sleepiestMin := -1
	sleepiestMinDays := -1
	for i := 0; i < 60; i++ {
		if sleepiestGuard.daysAsleepAtTime(i) > sleepiestMinDays {
			sleepiestMin = i
			sleepiestMinDays = sleepiestGuard.daysAsleepAtTime(i)
		}
	}

	fmt.Printf("sleepiest minute: %d\n", sleepiestMin)
}
