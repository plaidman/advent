from re import search

def crateMover(line: str, stacks: list[list[str]]):
    qty, src, dest = search('move (\d+) from (\d+) to (\d+)', line).group(1,2,3)

    src = int(src) - 1
    dest = int(dest) - 1
    qty = int(qty)

    splitAt = len(stacks[src]) - qty
    stacks[dest] += stacks[src][splitAt:]
    stacks[src] = stacks[src][:splitAt]
