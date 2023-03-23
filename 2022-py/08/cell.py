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

        self.tallestUp = -2
        self.tallestDown = -2
        self.tallestLeft = -2
        self.tallestRight = -2

        self.distanceUp = 0
        self.distanceDown = 0
        self.distanceLeft = 0
        self.distanceRight = 0

    def getTallestUp(self) -> tuple[int, int]:
        if self.tallestUp != -2:
            return self.tallestUp, self.distanceUp

        if self.y == 0:
            self.tallestUp = -1
        else:
            upCell = Cell.grid.getCell(self.x, self.y - 1)
            tallestUp, distanceUp = upCell.getTallestUp()

            if upCell.height >= tallestUp:
                self.tallestUp = upCell.height
            else:
                self.tallestUp = tallestUp

        return self.tallestUp, self.distanceUp

    def getTallestDown(self) -> tuple[int, int]:
        if self.tallestDown != -2:
            return self.tallestDown, self.distanceDown

        if self.y == Cell.grid.height - 1:
            self.tallestDown = -1
        else:
            downCell = Cell.grid.getCell(self.x, self.y + 1)
            tallestDown, distanceDown = downCell.getTallestDown()

            if downCell.height >= tallestDown:
                self.tallestDown = downCell.height
            else:
                self.tallestDown = tallestDown

        return self.tallestDown, self.distanceDown

    def getTallestLeft(self) -> tuple[int, int]:
        if self.tallestLeft != -2:
            return self.tallestLeft, self.distanceLeft

        if self.x == 0:
            self.tallestLeft = -1
        else:
            leftCell = Cell.grid.getCell(self.x - 1, self.y)
            tallestLeft, distanceLeft = leftCell.getTallestLeft()

            if leftCell.height >= tallestLeft:
                self.tallestLeft = leftCell.height
            else:
                self.tallestLeft = tallestLeft

        return self.tallestLeft, self.distanceLeft

    def getTallestRight(self) -> tuple[int, int]:
        if self.tallestRight != -2:
            return self.tallestRight, self.distanceRight

        if self.x == Cell.grid.width - 1:
            self.tallestRight = -1
        else:
            rightCell = Cell.grid.getCell(self.x + 1, self.y)
            tallestRight, distanceRight = rightCell.getTallestRight()

            if rightCell.height >= tallestRight:
                self.tallestRight = rightCell.height
            else:
                self.tallestRight = tallestRight

        return self.tallestRight, self.distanceRight

    def isVisible(self) -> bool:
        visible = False

        if self.height > self.getTallestUp()[0]:
            visible = True

        if self.height > self.getTallestDown()[0]:
            visible = True

        if self.height > self.getTallestLeft()[0]:
            visible = True

        if self.height > self.getTallestRight()[0]:
            visible = True

        return visible
