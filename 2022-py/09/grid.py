from __future__ import annotations

class Segment:
    def __init__(self, x, y) -> None:
        self.x = x; self.y = y
        self.next: Segment | None = None
        self.prev: Segment | None = None
    def key(self) -> str:
        return f'{self.x},{self.y}'
    def diff(self, other: Segment):
        return max(
            abs(self.x - other.x),
            abs(self.y - other.y),
        )

class Grid:
    def __init__(self, strlen: int) -> None:
        curSeg = Segment(0,0)
        self.head = curSeg
        self.tail = curSeg
        self.strlen = strlen

        for _ in range(1,strlen):
            newSeg = Segment(0,0)
            newSeg.prev = curSeg
            curSeg.next = newSeg
            self.tail = newSeg
            curSeg = newSeg

        self.visited = {}
        self.visited['0,0'] = True

    def pluckOne(self, curPos: Segment) -> None:
        if curPos.next == None:
            self.tail = curPos.prev
            self.tail.next = None
            self.visited[self.tail.key()] = True
            print('plucking tail')
            return

        print(f'checking {curPos.key()}')
        print(f'  prev {curPos.prev.key()}')
        print(f'  next {curPos.next.key()}')
        
        if curPos.prev.diff(curPos.next) > 1:
            print('  diff > 1, checking next')
            return self.pluckOne(curPos.next)

        curPos.next.prev = curPos.prev
        curPos.prev.next = curPos.next
        print('  plucking current')
        

    def moveHead(self, dir: str) -> None:
        curPos = self.head

        if dir == 'U':
            newPos = Segment(curPos.x, curPos.y - 1)
        elif dir == 'D':
            newPos = Segment(curPos.x, curPos.y + 1)
        elif dir == 'L':
            newPos = Segment(curPos.x - 1, curPos.y)
        elif dir == 'R':
            newPos = Segment(curPos.x + 1, curPos.y)


        print('----------------\n')
        print(f'created ({newPos.key()})')

        curPos.prev = newPos
        newPos.next = curPos
        self.head = newPos
        self.pluckOne(curPos)
