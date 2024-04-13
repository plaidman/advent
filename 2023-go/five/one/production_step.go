package one

type Mapping struct {
	start int
	end int
	mod int
}

type ProductionStep struct {
	mappings []Mapping
}

func NewProductionStep(mappings []Mapping) ProductionStep {
	return ProductionStep{
		mappings: mappings,
	}
}

func (ps *ProductionStep) mapNumber(number int) int {
	for _, mapping := range ps.mappings {
		if number <= mapping.end && number >= mapping.start {
			return number + mapping.mod
		}
	}

	return number
}
