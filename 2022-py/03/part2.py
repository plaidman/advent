def readfile(filename: str) -> list[str]:
    with open(filename, 'r') as file:
        return file.read().splitlines()


def charValue(char: str) -> int:
    if char.isupper():
        return ord(char) - 38
    else:
        return ord(char) - 96


def commonChars(str1: str, str2: str) -> str:
    common = ''

    for char in str1:
        if char in str2:
            common += char

    return common


input = readfile('input.txt')
count = int(len(input) / 3)
sum = 0

for i in range(count):
    base = i * 3
    common = commonChars(input[base].strip(), input[base+1].strip())
    common = commonChars(common, input[base+2].strip())
    
    sum += charValue(common[0])

print(sum)
