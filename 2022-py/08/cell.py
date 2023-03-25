from __future__ import annotations
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from grid import Grid

class Cell:
    grid: Grid = None

    def __init__(self, height: int, x: int, y: int) -> None:
        self.height = height
        self.x = x
        self.y = y

        self.blockUp: tuple[bool, int] = None
        self.blockDown: tuple[bool, int] = None
        self.blockLeft: tuple[bool, int] = None
        self.blockRight: tuple[bool, int] = None

    def findBlockerUp(self) -> tuple[int, bool]:
        if self.blockUp != None: return self.blockUp
        if self.y == 0: self.blockUp = (False, 0); return self.blockUp

        blocked = False
        for diff in range(self.y):
            diff += 1
            height = Cell.grid.getCell(self.x, self.y - diff).height
            if height >= self.height:
                blocked = True
                break
        
        self.distUp = (blocked, diff); return self.distUp

    def findBlockerDown(self) -> tuple[int, bool]:
        if self.blockDown != None: return self.blockDown
        if self.y == Cell.grid.height - 1: self.blockDown = (False, 0); return self.blockDown

        blocked = False
        for diff in range(Cell.grid.height - self.y - 1):
            diff += 1
            height = Cell.grid.getCell(self.x, self.y + diff).height
            if height >= self.height:
                blocked = True
                break
        
        self.distDown = (blocked, diff); return self.distDown

    def findBlockerLeft(self) -> tuple[int, bool]:
        if self.blockLeft != None: return self.blockLeft
        if self.x == 0: self.blockLeft = (False, 0); return self.blockLeft

        blocked = False
        for diff in range(self.x):
            diff += 1
            height = Cell.grid.getCell(self.x - diff, self.y).height
            if height >= self.height:
                blocked = True
                break
        
        self.distLeft = (blocked, diff); return self.distLeft

    def findBlockerRight(self) -> tuple[int, bool]:
        if self.blockRight != None: return self.blockRight
        if self.x == Cell.grid.width - 1: self.blockRight = (False, 0); return self.blockRight

        blocked = False
        for diff in range(Cell.grid.width - self.x - 1):
            diff += 1
            height = Cell.grid.getCell(self.x + diff, self.y).height
            if height >= self.height:
                blocked = True
                break
        
        self.distRight = (blocked, diff); return self.distRight

    def isVisible(self) -> bool:
        if self.findBlockerUp()[0] == False: return True
        if self.findBlockerDown()[0] == False: return True
        if self.findBlockerLeft()[0] == False: return True
        if self.findBlockerRight()[0] == False: return True
        return False

    def scenicScore(self) -> int:
        total = 1
        total *= self.findBlockerUp()[1]
        total *= self.findBlockerDown()[1]
        total *= self.findBlockerLeft()[1]
        total *= self.findBlockerRight()[1]
        return total