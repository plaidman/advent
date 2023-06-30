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
	parts["two"] = partOne

	parts[part](lines)
}

func partOne(lines []string) {
	events := CreateEventList(lines)
	guards := CreateGuardList(events)

	// for _, guard := range guards.guards {
	// 	guard.printGuard()
	// }

	// part 1
	guardSleepTime := -1
	var sleepiestGuard Guard
	for _, guard := range guards.guards {
		if guardSleepTime == -1 || guardSleepTime < guard.totalNapTime {
			guardSleepTime = guard.totalNapTime
			sleepiestGuard = *guard
		}
	}

	fmt.Printf("part 1: %d\n", sleepiestGuard.sleepiestMinute*sleepiestGuard.id)

	// part 2
	guardSleepDays := -1
	for _, guard := range guards.guards {
		if guardSleepDays == -1 || guardSleepDays < guard.daysAtMinute {
			guardSleepDays = guard.daysAtMinute
			sleepiestGuard = *guard
		}
	}

	fmt.Printf("part 2: %d\n", sleepiestGuard.sleepiestMinute*sleepiestGuard.id)
}
