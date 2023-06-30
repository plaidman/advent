package four

type GuardList struct {
	guards map[string]Guard
}

func CreateGuardList(events EventList) GuardList {
	guards := make(map[string]Guard)

	self := GuardList{guards: guards}
	self.populateGuardList(events)

	for _, guard := range self.guards {
		guard.parseSchedule()
	}

	return self
}

func (g GuardList) checkAndAppend(id string) Guard {
	guard, exists := g.guards[id]

	if !exists {
		guard = NewGuard(id)
		g.guards[id] = guard
	}

	return guard
}

func (g GuardList) populateGuardList(events EventList) {
	var currentGuard Guard

	for _, event := range *events.events {
		isGuardShift, id := event.isGuardShiftEvent()

		if isGuardShift {
			currentGuard = g.checkAndAppend(id)
		} else {
			currentGuard.appendEvent(event)
		}
	}
}

func (g GuardList) FindSleepiestGuard() Guard {
	sleepiest := NewGuard("temp")

	for _, guard := range g.guards {
		if *sleepiest.totalNapTime < *guard.totalNapTime {
			sleepiest = guard
		}
	}

	return sleepiest
}
