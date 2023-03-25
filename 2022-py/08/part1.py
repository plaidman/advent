from grid import Grid

with open('input.txt', 'r') as file:
    lines = file.read().splitlines()

grid = Grid(lines)

count = 0
for y in range(grid.height):
    for x in range(grid.width):
        if grid.getCell(x,y).isVisible():
            count += 1
print(f'count: {count}')

max = -1
for y in range(grid.height):
    for x in range(grid.width):
        scenicScore = grid.getCell(x,y).scenicScore()
        if scenicScore > max:
            max = scenicScore

print(f'max: {max}')
