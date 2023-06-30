package four

type GuardList struct {
	guards map[int]*Guard
}

func CreateGuardList(events EventList) GuardList {
	guards := make(map[int]*Guard)

	self := GuardList{guards: guards}
	self.populateGuardList(events)

	for _, guard := range self.guards {
		guard.parseSchedule()
		guard.findSleepiestMinute()
	}

	return self
}

func (g GuardList) checkAndAppend(id int) *Guard {
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
