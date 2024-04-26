package ten

import "fmt"

type Pawn struct {
	row   int
	col   int
	going byte
	steps int
}

func NewPawn(row int, col int, going byte) Pawn {
	return Pawn{
		row:   row,
		col:   col,
		going: going,
		steps: 0,
	}
}

func (p *Pawn) TakeStep(f *Field) {
	switch p.going {
	case 'n':
		p.row--
	case 's':
		p.row++
	case 'w':
		p.col--
	case 'e':
		p.col++
	}

	tileType := f.GetTileType(p.row, p.col)
	p.steps++
	p.going = tileType[p.going]
}

func (p *Pawn) ToString() string {
	return fmt.Sprintf(
		"pawn has taken %v steps, is on %v,%v, and is going %c",
		p.steps, p.row, p.col, rune(p.going),
	)
}
