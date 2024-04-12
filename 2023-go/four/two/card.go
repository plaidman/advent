package two

import "fmt"

type Card struct {
	id int
	winners []int
	have []int
	score int
	copies int
}

func NewCard(id int, winners []int, have []int) Card {
	return Card{
		id: id,
		winners: winners,
		have: have,
		copies: 1,
	}
}

func (c Card) String() string {
	return fmt.Sprintf("card: %v (%v), x%v", c.id, c.score, c.copies)
}
