class FS:
    smallDirSum = 0
    allFolderSizes: list['FS'] = []

    def __init__(self, up: 'FS') -> None:
        self.dirs: dict[str, FS] = {}
        self.files: dict[str, int] = {}
        self.up = self
        self.root = self

        if up != None:
            self.up = up
            self.root = up.root

    def mkdir(self, name: str):
        self.dirs[name] = FS(self)

    def touch(self, name: str, size: int):
        self.files[name] = size

    def cd(self, name: str):
        if name == '..':
            return self.up
        elif name == '/':
            return self.root
        else:
            return self.dirs[name]

    def size(self, path: str) -> int:
        dirSize = 0
        print(f'sizing {path}')

        for value in self.files.values():
            dirSize += value

        for dirname, subdir in self.dirs.items():
            size = subdir.size(f'{path}{dirname}/')
            dirSize += size

        if dirSize < 100000:
            print(f'found {path}: {dirSize}')
            FS.smallDirSum += dirSize

        FS.allFolderSizes.append(dirSize)
        return dirSize
