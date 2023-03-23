def value(char):
    if char.isupper():
        return ord(char) - 38
    else:
        return ord(char) - 96

input = []
with open("input.txt", "r") as file:
    line = file.readline()
    while line:
        input.append(line.strip())
        line = file.readline()

sum = 0
letter = ''
for line in input:
    length = int(len(line)/2)

    for x in range(length):
        for y in range(length):
            if (line[x] == line[y+length]):
                letter = line[x]
                break

        if (letter != ''):
            break

    sum += value(letter)
    letter = ''

print(sum)
