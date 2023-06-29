package four

import "fmt"

type Guard struct {
	id           string
	events       *[]Event
	naps         *[]Nap
	totalNapTime int
}

func NewGuard(id string) Guard {
	events := make([]Event, 0)
	naps := make([]Nap, 0)

	return Guard{id: id, naps: &naps, totalNapTime: 0, events: &events}
}

func (g Guard) printGuard() {
	fmt.Println("----------------------")
	fmt.Printf("guard #%s:\n", g.id)

	for _, event := range *g.events {
		fmt.Println("  " + event.toString())
	}

	fmt.Println("----------------------")
}

func (g Guard) appendEvent(event Event) {
	*g.events = append(*g.events, event)
}
