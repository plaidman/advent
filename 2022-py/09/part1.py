from grid import Grid
from re import search

with open('input.txt', 'r') as file:
    lines = file.read().splitlines()

grid = Grid(10)

for line in lines:
    dir, count = search('(U|D|L|R) (\d+)', line).group(1,2)
    for _ in range(int(count)):
        grid.moveHead(dir)

print(grid.visited)
print(len(grid.visited.keys()))
