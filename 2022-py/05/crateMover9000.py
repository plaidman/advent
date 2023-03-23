from re import search

def crateMover(line: str, stacks: list[list[str]]):
    qty, src, dest = search('move (\d+) from (\d+) to (\d+)', line).group(1,2,3)

    for x in range(int(qty)):
        label = stacks[int(src)-1].pop()
        stacks[int(dest)-1].append(label)
