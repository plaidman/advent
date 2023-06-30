package four

type GuardList struct {
	guards map[string]*Guard
}

func CreateGuardList(events EventList) GuardList {
	guards := make(map[string]*Guard)

	self := GuardList{guards: guards}
	self.populateGuardList(events)

	for _, guard := range self.guards {
		guard.parseSchedule()
	}

	return self
}

func (g GuardList) checkAndAppend(id string) *Guard {
	guardPtr, exists := g.guards[id]

	if !exists {
		guard := NewGuard(id)
		guardPtr = &guard
		g.guards[id] = guardPtr
	}

	return guardPtr
}

func (g GuardList) populateGuardList(events EventList) {
	var currentGuard *Guard

	for _, event := range events.events {
		isGuardShift, id := event.isGuardShiftEvent()

		if isGuardShift {
			currentGuard = g.checkAndAppend(id)
		} else {
			currentGuard.appendEvent(event)
		}
	}
}

func (g GuardList) FindSleepiestGuard() *Guard {
	var sleepiestGuard *Guard
	guardNapTime := -1

	for _, guardPtr := range g.guards {
		if guardNapTime == -1 || guardNapTime < guardPtr.totalNapTime {
			sleepiestGuard = guardPtr
			guardNapTime = guardPtr.totalNapTime
		}
	}

	return sleepiestGuard
}
