package four

import (
	"fmt"
	"os"
	"regexp"
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

func parseLine(line string) (string, string, string, string, string) {
	pattern := regexp.MustCompile("^\\[\\d+-(\\d+)-(\\d+) (\\d+):(\\d+)] (.+)$")
	matches := pattern.FindStringSubmatch(line)
	return matches[1], matches[2], matches[3], matches[4], matches[5]
}

func partOne(lines []string) {
	events := NewEventList()
	guards := NewGuardList()

	// grab all events
	for _, line := range lines {
		month, day, hour, minute, desc := parseLine(line)
		event := Event{month, day, hour, minute, desc}
		events.appendEvent(event)
	}

	events.sortList()

	// populate guards with events
	currentGuard := "0"
	for _, event := range *events.events {
		isGuardShift, id := event.isGuardShift()

		if isGuardShift {
			currentGuard = id
			guards.checkAndAppend(id)
			fmt.Printf("switching to guard %s\n", id)
		} else {
			guards.guards[currentGuard].appendEvent(event)
		}
	}

	for _, guard := range guards.guards {
		guard.printGuard()
	}

}
