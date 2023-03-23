line = ''
with open('input.txt', 'r') as file:
    line = file.readline().strip()
windowLength = 14

def findMatch(string: str) -> int:
    for i in range(windowLength):
        if string[i] in string[i+1:]:
            return i
    return -1

i = 0
while i < len(line) - windowLength - 1:
    substr = line[i:i+windowLength]
    matchIndex = findMatch(substr)
    if matchIndex == -1:
        break
    i += 1

print(i+windowLength)
