package two

func NewHandRanker(in chan Hand) chan Hand {
	return NewPipelineStep(in, rankHand)
}

func rankHand(in Hand) Hand {
	uniqueCards := make(map[int]int)

	for _, card := range in.cards {
		uniqueCards[card]++
	}

	if uniqueCards[1] > 0 {
		uniqueCards = applyJokers(uniqueCards)
	}

	switch len(uniqueCards) {
	case 1: // five of a kind
		in.rank = 7
	case 2: // full house or four of a kind
		in.rank = rankTwo(uniqueCards)
	case 3: // two pair or three of a kind
		in.rank = rankThree(uniqueCards)
	case 4: // pair
		in.rank = 2
	case 5: // high card
		in.rank = 1
	}

	return in
}

func applyJokers(uniqueCards map[int]int) map[int]int {
	numJokers := uniqueCards[1]
	delete(uniqueCards, 1)

	mostCard := 0
	mostQty := 0
	for card, qty := range uniqueCards {
		if mostQty < qty {
			mostCard = card
			mostQty = qty
		}
	}

	uniqueCards[mostCard] += numJokers

	return uniqueCards
}

func rankTwo(cards map[int]int) int {
	for _, qty := range cards {
		if qty == 3 || qty == 2 {
			return 5 // full house
		}
	}

	return 6 // four of a kind
}

func rankThree(cards map[int]int) int {
	for _, qty := range cards {
		if qty == 2 {
			return 3 // two pair
		}
	}

	return 4 // three of a kind
}
