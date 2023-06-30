package four

import (
	"fmt"
	"regexp"
	"strconv"
)

type Event struct {
	month  string
	day    string
	hour   string
	minute string
	desc   string
}

func (e Event) toString() string {
	return fmt.Sprintf("%s/%s %s:%s - %s", e.month, e.day, e.hour, e.minute, e.desc)
}

func (e Event) stamp() int {
	i, _ := strconv.Atoi(fmt.Sprintf("%s%s%s%s", e.month, e.day, e.hour, e.minute))
	return i
}

func (e Event) isGuardShiftEvent() (bool, string) {
	pattern := regexp.MustCompile("Guard #(\\d+) begins shift")
	matches := pattern.FindStringSubmatch(e.desc)

	if matches == nil {
		return false, ""
	}

	return true, matches[1]
}
