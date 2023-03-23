input = []
with open("input.txt", "r") as file:
    line = file.readline()
    while line:
        input.append(line.strip())
        line = file.readline()

scores_1 = {
    'A X': 1+3,
    'A Y': 2+6,
    'A Z': 3+0,
    'B X': 1+0,
    'B Y': 2+3,
    'B Z': 3+6,
    'C X': 1+6,
    'C Y': 2+0,
    'C Z': 3+3,
}

scores_2 = {
    'A X': scores_1['A Z'],
    'A Y': scores_1['A X'],
    'A Z': scores_1['A Y'],
    'B X': scores_1['B X'],
    'B Y': scores_1['B Y'],
    'B Z': scores_1['B Z'],
    'C X': scores_1['C Y'],
    'C Y': scores_1['C Z'],
    'C Z': scores_1['C X'],
}

total = 0
for line in input:
    total += scores_2[line]
print(total)