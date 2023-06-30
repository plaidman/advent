package four

import (
	"regexp"
	"sort"
)

type EventList struct {
	events *[]Event
}

func CreateEventList(lines []string) EventList {
	events := make([]Event, 0)

	self := EventList{events: &events}

	self.parseLines(lines)
	self.sortList()

	return self
}

func (e EventList) appendEvent(event Event) {
	*e.events = append(*e.events, event)
}

func (e EventList) sortList() {
	sort.Slice(*e.events, func(i, j int) bool {
		events := *e.events
		return events[i].stamp() < events[j].stamp()
	})
}

func (e EventList) parseLines(lines []string) {
	for _, line := range lines {
		month, day, hour, minute, desc := parseLine(line)
		event := Event{month, day, hour, minute, desc}
		e.appendEvent(event)
	}
}

func parseLine(line string) (string, string, string, string, string) {
	pattern := regexp.MustCompile("^\\[\\d+-(\\d+)-(\\d+) (\\d+):(\\d+)] (.+)$")
	matches := pattern.FindStringSubmatch(line)
	return matches[1], matches[2], matches[3], matches[4], matches[5]
}
