package ten

import (
	"regexp"
)

type Directions map[byte]byte
type TileTypes map[byte]Directions

type Field struct {
	tileMap   []string
	startRow  int
	startCol  int
	tileTypes TileTypes
}

func NewField() *Field {
	return &Field{
		tileMap: make([]string, 0),
		tileTypes: TileTypes{
			'|': Directions{'n': 'n', 's': 's'},
			'-': Directions{'e': 'e', 'w': 'w'},
			'F': Directions{'n': 'e', 'w': 's'},
			'7': Directions{'n': 'w', 'e': 's'},
			'L': Directions{'s': 'e', 'w': 'n'},
			'J': Directions{'s': 'w', 'e': 'n'},
			'.': Directions{},
		},
	}
}

func (f *Field) AddLine(line string) {
	startPattern := regexp.MustCompile(`(S)`)

	f.tileMap = append(f.tileMap, line)

	match := startPattern.FindStringIndex(line)
	if match != nil {
		f.startRow = len(f.tileMap) - 1
		f.startCol = match[0]
	}
}

func (f *Field) FindTravelers() []Pawn {
	pawns := make([]Pawn, 0, 2)

	tileType := f.GetTileType(f.startRow-1, f.startCol)
	if tileType['n'] != 0 {
		pawns = append(pawns, NewPawn(f.startRow, f.startCol, 'n'))
	}

	tileType = f.GetTileType(f.startRow+1, f.startCol)
	if tileType['s'] != 0 {
		pawns = append(pawns, NewPawn(f.startRow, f.startCol, 's'))
	}

	tileType = f.GetTileType(f.startRow, f.startCol-1)
	if tileType['w'] != 0 {
		pawns = append(pawns, NewPawn(f.startRow, f.startCol, 'w'))
	}

	tileType = f.GetTileType(f.startRow, f.startCol+1)
	if tileType['e'] != 0 {
		pawns = append(pawns, NewPawn(f.startRow, f.startCol, 'e'))
	}

	return pawns
}

func (f *Field) GetTileType(row int, col int) Directions {
	if row == -1 || row == len(f.tileMap) {
		return f.tileTypes['.']
	}

	if col == -1 || col == len(f.tileMap[0]) {
		return f.tileTypes['.']
	}

	tile := f.tileMap[row][col]
	return f.tileTypes[tile]
}

func (f *Field) FindMidpoint(pawns []Pawn) int {
	one := pawns[0]
	two := pawns[1]

	for {
		one.TakeStep(f)
		two.TakeStep(f)

		if one.row == two.row && one.col == two.col {
			return one.steps
		}
	}
}
