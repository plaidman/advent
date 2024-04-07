package one

import (
	"sync"
)

type Verifier struct {
	Out       chan Part
	in        chan Part
	schem     *Schematic
	waitGroup sync.WaitGroup
}

func NewVerifier(schem *Schematic, in chan Part) *Verifier {
	return &Verifier{
		Out:       make(chan Part),
		in:        in,
		schem:     schem,
		waitGroup: sync.WaitGroup{},
	}
}

func (v *Verifier) WaitForClose() {
	v.waitGroup.Wait()
	close(v.Out)
}

func (v *Verifier) WaitForParts() {
	go func() {
		for part := range v.in {
			v.AddPart(part)
		}
	}()
}

func (v *Verifier) AddPart(part Part) {
	v.waitGroup.Add(1)
	go v.verifyPart(part)
}

func (v *Verifier) verifyPart(part Part) {
	defer v.waitGroup.Done()

	surr := v.schem.GetSurrounding(part)

	for _, line := range surr {
		for _, char := range line {
			if (char > '9' || char < '0') && char != '.' {
				v.Out <- part
				return;
			}
		}
	}
}
