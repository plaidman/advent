package four

import "sort"

type EventList struct {
	events *[]Event
}

func NewEventList() EventList {
	events := make([]Event, 0)

	return EventList{events: &events}
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
