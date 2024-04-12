package two

import (
	"sync"
)

type CardMatchCounter struct {
	count int
	mutex sync.Mutex
	wg    sync.WaitGroup
}

func NewCardScorer(in chan Card) chan Card {
	return NewPipelineStep(in, scoreCard)
}

func scoreCard(card Card) Card {
	matchCounter := &CardMatchCounter{}

	for _, winner := range card.winners {
		matchCounter.wg.Add(1)
		go findMatches(winner, card.have, matchCounter)
	}

	matchCounter.wg.Wait()
	card.score = matchCounter.count
	return card
}

func findMatches(winner int, numbers []int, score *CardMatchCounter) {
	defer score.wg.Done()

	for _, number := range numbers {
		if winner == number {
			score.mutex.Lock()
			score.count++
			score.mutex.Unlock()
			return
		}
	}
}
