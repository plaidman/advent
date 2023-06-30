package four

import (
	"fmt"
	"strconv"
)

type Guard struct {
	id           string
	events       *[]Event
	days         DayList
	totalNapTime *int
}

func NewGuard(id string) Guard {
	events := make([]Event, 0)
	days := NewDayList()
	totalNapTime := 0

	return Guard{id: id, days: days, totalNapTime: &totalNapTime, events: &events}
}

func (g Guard) printGuard() {
	fmt.Println("----------------------")
	fmt.Printf("guard #%s:\n", g.id)
	fmt.Printf("  totalNap %d:\n", *g.totalNapTime)
	fmt.Println("---")

	for _, event := range *g.events {
		fmt.Println("  " + event.toString())
	}

	fmt.Println("---")

	for date, day := range g.days.days {
		fmt.Println("  date " + date)

		for _, nap := range *day.naps {
			fmt.Printf("    from %d to %d, total %d\n", nap.startMin, nap.endMin, nap.diff)
		}
	}

	fmt.Println("----------------------")
}

func (g Guard) appendEvent(event Event) {
	*g.events = append(*g.events, event)
}

func (g Guard) parseSchedule() {
	events := *g.events
	for i := 0; i < len(events); i += 2 {
		date := events[i].month + events[i].day
		startMin, _ := strconv.Atoi(events[i].minute)
		endMin, _ := strconv.Atoi(events[i+1].minute)

		day := g.days.checkAndAppend(date)
		nap := NewNap(startMin, endMin)
		day.appendNap(nap)

		*g.totalNapTime += nap.diff
	}
}

func (g Guard) daysAsleepAtTime(min int) int {
	daysAsleep := 0

	for _, day := range g.days.days {
		if day.asleepAtTime(min) {
			daysAsleep++
		}
	}

	return daysAsleep
}
