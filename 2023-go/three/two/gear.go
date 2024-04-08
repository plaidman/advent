package two

type Gear struct {
	row int
	col int
	parts []Part
}

func NewGear(row int, col int) *Gear {
	return &Gear{row, col, nil}
}

func (g *Gear) AddParts(parts []Part) {
	g.parts = parts
}
