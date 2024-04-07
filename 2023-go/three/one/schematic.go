package one

import (
	"strconv"
)

type Schematic struct {
	schem   []string
	lastRow int
	lastCol int
}

func NewSchematic() *Schematic {
	return &Schematic{
		schem:   make([]string, 0),
		lastRow: -1,
		lastCol: 0,
	}
}

func (s *Schematic) AddLine(line string) {
	s.schem = append(s.schem, line)

	s.lastRow++
	if s.lastCol == 0 {
		s.lastCol = len(line)
	}
}

func (s *Schematic) GetSurrounding(part Part) []string {
	surr := make([]string, 0, 3)
	start := max(0, part.start-1)
	end := min(s.lastCol, part.end+1)

	if part.row > 0 {
		surr = append(surr, s.schem[part.row-1][start:end])
	}

	surr = append(surr, s.schem[part.row][start:end])

	if part.row < s.lastRow {
		surr = append(surr, s.schem[part.row+1][start:end])
	}

	return surr
}

func (s *Schematic) GetPartNumber(part Part) int {
	numString := s.schem[part.row][part.start:part.end]

	partNum, _ := strconv.Atoi(numString)

	return partNum
}

func (s *Schematic) ForEachRow(callback func(int, string)) {
	for rowNum, line := range s.schem {
		callback(rowNum, line)
	}
}
