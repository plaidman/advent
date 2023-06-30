package five

import "fmt"

type Unit struct {
	element  rune
	isUpper  bool
	nextUnit *Unit
	prevUnit *Unit
}

func NewUnit(element rune) *Unit {
	if element < 91 {
		return &Unit{element: element, isUpper: true}
	}

	return &Unit{element: element - 32, isUpper: false}
}

func (u *Unit) letter() string {
	if u.isUpper {
		return fmt.Sprintf("%c", u.element)
	}

	return fmt.Sprintf("%c", u.element+32)
}

func (u *Unit) insertAfter(prev *Unit) {
	next := prev.nextUnit

	u.prevUnit = prev
	u.nextUnit = next
	prev.nextUnit = u

	if next != nil {
		next.prevUnit = u
	}
}

func (u Unit) clashesWithNext() bool {
	next := u.nextUnit
	return u.element == next.element && u.isUpper != next.isUpper
}

func (u *Unit) destroyPair() *Unit {
	prev := u.prevUnit
	next := u.nextUnit.nextUnit

	if next != nil {
		next.prevUnit = prev
	}

	if prev == nil {
		return next
	}

	prev.nextUnit = next
	return prev
}
