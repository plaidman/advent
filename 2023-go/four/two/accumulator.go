package two

func Accumulate(in chan Card) chan []Card {
	out := make(chan []Card)

	go func() {
		cards := make([]Card, 0)

		for card := range in {
			cards = append(cards, card)
		}

		out <- cards
	}()

	return out
}
