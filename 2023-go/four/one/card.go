package one

import "fmt"

type Card struct {
	id int
	winners []int
	have []int
}

func NewCard(id int, winners []int, have []int) Card {
	return Card{
		id: id,
		winners: winners,
		have: have,
	}
}

func (c Card) String() string {
	return fmt.Sprintf(
		"card: %v\n  winners: %v\n     have: %v\n------------------\n",
		c.id,
		c.winners,
		c.have,
	)
}
