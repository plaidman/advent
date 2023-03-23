from filesystem import FS
from re import search

drive = FS(None)

with open('input.txt', 'r') as file:
    line = file.readline().strip()
    while line:
        if line.startswith('$ cd '):
            drive = drive.cd(line[5:])
        elif line.startswith('$ ls'):
            pass
        elif line.startswith('dir '):
            drive.mkdir(line[4:])
        else:
            size, name = search('(\d+) (.*)', line).group(1, 2)
            drive.touch(name, int(size))

        line = file.readline().strip()

drive = drive.cd('/')
rootSize = drive.size('/')
freeSpace = 70000000 - rootSize
neededSpace = 30000000 - freeSpace

print(f'sum of small dirs: {FS.smallDirSum}')
print('')
print(f'need {neededSpace}')

FS.allFolderSizes[:] = [size for size in FS.allFolderSizes if size >= neededSpace]
FS.allFolderSizes.sort()
print(FS.allFolderSizes[0])