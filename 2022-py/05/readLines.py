def readLines(filename: str) -> tuple[list[str], list[str]]:
    stackLines: list[str] = []
    moveLines: list[str] = []
    
    with open(filename, 'r') as file:
        line = file.readline().strip('\n')
        while line != '':
            stackLines.append(line)
            line = file.readline().strip('\n')
        stackLines.reverse()
        stackLines.pop(0)

        line = file.readline().strip('\n')
        while line:
            moveLines.append(line)
            line = file.readline().strip('\n')
    
    return stackLines, moveLines
