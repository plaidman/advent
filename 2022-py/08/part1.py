from grid import Grid

with open('test.txt', 'r') as file:
    lines = file.read().splitlines()

grid = Grid(lines)

count = 0
for y in range(grid.height):
    for x in range(grid.width):
        if grid.getCell(x,y).isVisible():
            count += 1
print(f'count: {count}')

# for y in range(grid.height):
#     for x in range(grid.width):
#         print(grid.getCell(x,y).scenicScore())
