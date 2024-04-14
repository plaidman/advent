package one

type Hand struct {
	cards [5]int
	rank int
	bid int
}

func SortHandFunc(hands []Hand) func (a int, b int) bool {
	return func (a int, b int) bool {
		first := hands[a]
		second := hands[b]

		if first.rank == second.rank {
			return cardsLessThan(first, second)
		}

		return first.rank < second.rank
	}
}

func cardsLessThan(a, b Hand) bool {
	for i := 0; i < len(a.cards); i++ {
		if a.cards[i] == b.cards[i] {
			continue
		}

		return a.cards[i] < b.cards[i]
	}

	panic("hands are equal")
}
