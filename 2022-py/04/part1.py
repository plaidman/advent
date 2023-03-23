import re

def readfile(filename: str) -> list[str]:
    with open(filename, 'r') as file:
        return file.read().splitlines()

class Range:
    def __init__(self, min: int, max: int) -> None:
        self.min = min
        self.max = max

    def includes(self, other) -> bool:
        return self.min <= other.min and self.max >= other.max

    def overlaps(self, other) -> bool:
        if other.min >= self.min and other.min <= self.max:
            return True
        if other.max >= self.min and other.max <= self.max:
            return True
        return False

def parseLine(line: str) -> list[Range]:
    search = re.search('(\d+)-(\d+),(\d+)-(\d+)', line)
    return [
        Range(int(search.group(1)), int(search.group(2))),
        Range(int(search.group(3)), int(search.group(4))),
    ]

input = readfile('input.txt')
count = 0
for line in input:
    pair = parseLine(line)

    if pair[0].overlaps(pair[1]):
        count += 1
        continue

    if pair[1].overlaps(pair[0]):
        count += 1

print(count)