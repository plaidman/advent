def initStacks(numStacks: int, stackLines: list[str]) -> list[list[str]]:
    stacks: list[list[str]] = []

    for i in range(numStacks):
        stack: list[str] = []
        col = (i * 4) + 1

        for row in range(len(stackLines)):
            label = stackLines[row][col]

            if label == ' ':
                break

            stack.append(label)

        stacks.append(stack)

    return stacks