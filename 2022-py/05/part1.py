from readLines import readLines
from initStacks import initStacks
from crateMover9001 import crateMover

stackLines, moveLines = readLines('input.txt')
stacks = initStacks(9, stackLines)

for i, line in enumerate(moveLines):
    crateMover(line, stacks)

for stack in stacks:
    print('  ' + ''.join(stack))
