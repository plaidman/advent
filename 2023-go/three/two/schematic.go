package two

import "strconv"

type Schematic struct {
	schem []string
	rows  int
	cols  int
}

func NewSchematic() *Schematic {
	return &Schematic{
		schem: make([]string, 0),
		rows:  0,
		cols:  0,
	}
}

func (s *Schematic) AddLine(line string) {
	s.schem = append(s.schem, line)

	s.rows++
	if s.cols == 0 {
		s.cols = len(line)
	}
}

func (s *Schematic) ForEachRow(callback func(int, string)) {
	for rowNum, line := range s.schem {
		callback(rowNum, line)
	}
}

func (s *Schematic) isNumber(row int, col int) bool {
	switch {
	case row < 0:
		return false
	case row >= s.rows:
		return false
	case col < 0:
		return false
	case col >= s.cols:
		return false
	case s.schem[row][col] < '0':
		return false
	case s.schem[row][col] > '9':
		return false
	default:
		return true
	}
}

func (s *Schematic) GearParts(gear Gear) []Part {
	parts := make([]Part, 0, 2)

	north := s.isNumber(gear.row-1, gear.col)
	if north {
		parts = append(parts, Part{gear.row - 1, gear.col, 1})
	}

	south := s.isNumber(gear.row+1, gear.col)
	if south {
		parts = append(parts, Part{gear.row + 1, gear.col, 1})
	}

	if s.isNumber(gear.row, gear.col+1) {
		parts = append(parts, Part{gear.row, gear.col + 1, 1})
	}

	if s.isNumber(gear.row, gear.col-1) {
		parts = append(parts, Part{gear.row, gear.col - 1, 1})
	}

	if !north {
		if s.isNumber(gear.row-1, gear.col+1) {
			parts = append(parts, Part{gear.row - 1, gear.col + 1, 1})
		}

		if s.isNumber(gear.row-1, gear.col-1) {
			parts = append(parts, Part{gear.row - 1, gear.col - 1, 1})
		}
	}

	if !south {
		if s.isNumber(gear.row+1, gear.col+1) {
			parts = append(parts, Part{gear.row + 1, gear.col + 1, 1})
		}

		if s.isNumber(gear.row+1, gear.col-1) {
			parts = append(parts, Part{gear.row + 1, gear.col - 1, 1})
		}
	}

	return parts
}

func (s *Schematic) ParsePart(part Part) Part {
	for {
		if !s.isNumber(part.row, part.start-1) {
			break
		}

		part.start--
		part.length++
	}

	for {
		if !s.isNumber(part.row, part.start + part.length) {
			break
		}

		part.length++
	}

	return part
}

func (s *Schematic) GetPartNum(part Part) int {
	end := part.start + part.length
	numString := s.schem[part.row][part.start:end]

	partNum, _ := strconv.Atoi(numString)

	return partNum
}
