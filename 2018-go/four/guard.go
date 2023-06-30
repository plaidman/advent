package four

import (
	"fmt"
	"strconv"
)

type Guard struct {
	id              int
	events          []Event
	days            DayList
	totalNapTime    int
	sleepiestMinute int
	daysAtMinute    int
}

func NewGuard(id int) Guard {
	events := make([]Event, 0)
	days := NewDayList()

	guard := Guard{id: id, days: days, totalNapTime: 0, events: events}

	return guard
}

func (g Guard) printGuard() {
	fmt.Println("----------------------")
	fmt.Printf("guard #%d:\n", g.id)
	fmt.Printf("  totalNap %d:\n", g.totalNapTime)
	fmt.Printf("  sleepiestMinute %d:\n", g.sleepiestMinute)
	fmt.Printf("  daysAtMinute %d:\n", g.daysAtMinute)
	fmt.Println("---")

	for _, event := range g.events {
		fmt.Println("  " + event.toString())
	}

	fmt.Println("---")

	for date, day := range g.days.days {
		fmt.Println("  date " + date)

		for _, nap := range day.naps {
			fmt.Printf("    from %d to %d, total %d\n", nap.startMin, nap.endMin, nap.diff)
		}
	}

	fmt.Println("----------------------")
}

func (g *Guard) appendEvent(event Event) {
	g.events = append(g.events, event)
}

func (g *Guard) parseSchedule() {
	for i := 0; i < len(g.events); i += 2 {
		date := g.events[i].month + g.events[i].day
		startMin, _ := strconv.Atoi(g.events[i].minute)
		endMin, _ := strconv.Atoi(g.events[i+1].minute)

		day := g.days.checkAndAppend(date)
		nap := NewNap(startMin, endMin)
		day.appendNap(nap)

		g.totalNapTime += nap.diff
	}
}

func (g *Guard) findSleepiestMinute() {
	sleepiestMinute := -1
	daysAtMinute := -1

	for i := 0; i < 60; i++ {
		daysAtMinuteI := g.daysAsleepAtMinute(i)

		if daysAtMinuteI > daysAtMinute {
			sleepiestMinute = i
			daysAtMinute = daysAtMinuteI
		}
	}

	g.daysAtMinute = daysAtMinute
	g.sleepiestMinute = sleepiestMinute
}

func (g Guard) daysAsleepAtMinute(min int) int {
	daysAsleep := 0

	for _, day := range g.days.days {
		if day.asleepAtTime(min) {
			daysAsleep++
		}
	}

	return daysAsleep
}
