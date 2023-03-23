input = []
with open("input.txt", "r") as file:
    line = file.readline()
    while line:
        input.append(line.strip())
        line = file.readline()

elfCals = []
curCals = 0
for line in input:
    if len(line) == 0:
        elfCals.append(curCals)
        curCals = 0
        continue
    curCals += int(line)
elfCals.append(curCals)
elfCals.sort(reverse=True)

print(elfCals[0])
print(elfCals[0] + elfCals[1] + elfCals[2])