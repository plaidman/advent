package one

import "sync"

func NewPipelineStep[In, Out any](in chan In, compute func(In) Out) chan Out {
	out := make(chan Out)

	go func() {
		defer close(out)

		var currMutex *sync.Mutex // rotating mutex keeps things in order and acts as a waitgroup

		for task := range in {
			nextMutex := &sync.Mutex{}
			nextMutex.Lock()

			go func(currMutex *sync.Mutex, nextMutex *sync.Mutex, task In) {
				result := compute(task)

				if currMutex != nil { currMutex.Lock() } // block to avoid sending out of order
				out <- result
				nextMutex.Unlock() // unblock the next worker in the pipeline
			}(currMutex, nextMutex, task)

			currMutex = nextMutex
		}

		if currMutex != nil {
			currMutex.Lock() // wait for the last mutex to unlock
		}
	}()

	return out
}
