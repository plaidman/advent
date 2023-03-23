from cell import Cell

class Grid:
    def __init__(self, lines: list[str]) -> None:
        self.width = len(lines[0])
        self.height = len(lines)

        Cell.grid = self
        self.cells: list[list[Cell]] = []
        for y, line in enumerate(lines):
            row: list[Cell] = []

            for x, height in enumerate(line):
                row.append(Cell(int(height), x, y))

            self.cells.append(row)

    def getCell(self, x: int, y: int) -> Cell:
        return self.cells[y][x]
