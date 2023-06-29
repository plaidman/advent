package four

type GuardList struct {
	guards map[string]Guard
}

func NewGuardList() GuardList {
	guards := make(map[string]Guard)

	return GuardList{guards: guards}
}

func (g GuardList) checkAndAppend(id string) {
	_, exists := g.guards[id]

	if !exists {
		g.guards[id] = NewGuard(id)
	}
}
