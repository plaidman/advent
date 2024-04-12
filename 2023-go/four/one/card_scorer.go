package one

import (
	"sync"
)

type CardMatchCounter struct {
	count int
	mutex sync.Mutex
	wg    sync.WaitGroup
}

func NewCardScorer(in chan Card) chan int {
	return NewPipelineStep(in, scoreCard)
}

func scoreCard(card Card) int {
	matchCounter := &CardMatchCounter{}

	for _, winner := range card.winners {
		matchCounter.wg.Add(1)
		go findMatches(winner, card.have, matchCounter)
	}

	matchCounter.wg.Wait()
	return calculateScore(matchCounter.count)
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

func calculateScore(matches int) int {
	if matches == 0 {
		return 0
	}

	result := 1
	matches--
	for matches > 0 {
		result *= 2
		matches--
	}

	return result
}
