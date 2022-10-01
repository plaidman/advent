#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Source struct Source
#define Dest struct Dest
#define Cell struct Cell

Source {
    char label;
    int x;
    int y;
    Dest* destHead;
    Source* next;
};

Dest {
    Source* source;
    int dist;
    int doors; // bit mask
    Dest* next;
};

#define ROWS 81
#define COLS 81

void readInput(char*);
void initGlobals();
Source* newSource(char, int, int);
Dest* newDest(Source*, int, int);
void findAllDests(Source*);
int addDoor(char, int);
int addKey(char, int);
int isBlocked(int, int);
void printSrc(Source*);
void runDijkstra(int, int, int);
void resetDijkstra();
int findDoors(int, int, int);
int haveKey(char, int);
int search(Source*, int, int);

char map[ROWS][COLS+1];
int dijkstraMap[ROWS][COLS];
Source* sourceHead;
int allKeys;

int main(int argc, char const *argv[]) {
    initGlobals();
    readInput("input.txt");

    for(int y = 0; y < ROWS; y++) {
        printf("%s\n", map[y]);
    }
    printf("\n");

    Source* currSrc = sourceHead;
    while (currSrc != NULL) {
        if (currSrc->label != '@') {
            allKeys = addKey(currSrc->label, allKeys);
        }

        findAllDests(currSrc);
        printSrc(currSrc);

        currSrc = currSrc->next;
    }
    printf("\n");
    
    Source* start = sourceHead;
    while (start->label != '@') {
        start = start->next;
    }
    printf("start x %d, y %d\n", start->x, start->y);
    printf("all keys %d\n\n", allKeys);

    getchar();

    int lowest = search(start, 0, 0);
    printf("lowest: %d\n", lowest);

    exit(0);
}

int search(Source* source, int keys, int indentation) {
    if (indentation < 11) {
        printf("indentaiton %d\n", indentation);
    }

    if (source->label != '@') {
        // printf("adding key %c\n", source->label);
        keys = addKey(source->label, keys);
    }

    if (keys == allKeys) {
        // printf("have all keys\n");
        return 0;
    }

    Dest* minDest = source->destHead;
    int minDist = 9999999;

    Dest* dest = source->destHead;
    while (dest != NULL) {
        if (haveKey(dest->source->label, keys) == 1) {
            // printf("already have %c, skipping\n", dest->source->label);
            dest = dest->next;
            continue;
        }

        if (isBlocked(dest->doors, keys) == 1) {
            // printf("path %c -> %c is blocked\n", source->label, dest->source->label);
            dest = dest->next;
            continue;
        }

        // printf("looking at %c -> %c\n", source->label, dest->source->label);
        int result = search(dest->source, keys, indentation + 1);
        result += dest->dist;
        // printf("found %c -> %c: %d\n", source->label, dest->source->label, result);

        if (result < minDist) {
            minDist = result;
            minDest = dest;
        }

        dest = dest->next;
    }

    // printf("smallest %c -> %c: %d\n", source->label, minDest->source->label, minDist);
    // getchar();
    return minDist;
}

void printSrc(Source* source) {
    printf("%c %d %d\n", source->label, source->x, source->y);

    Dest* currDest = source->destHead;
    while (currDest != NULL) {
        printf("  %c %d %d\n", currDest->source->label, currDest->dist, currDest->doors);
        currDest = currDest->next;
    }
}

int isBlocked(int doors, int keys) {
    if ((keys | doors) == keys) {
        return 0;
    }

    return 1;
}

int haveKey(char key, int keys) {
    int shift = key - 'a';
    int binary = 1 << shift;

    if ((keys & binary) == 0) {
        return 0;
    }

    return 1;
}

int addDoor(char door, int doors) {
    int shift = door - 'A';
    int binary = 1 << shift;
    return doors | binary;
}

int addKey(char key, int keys) {
    int shift = key - 'a';
    int binary = 1 << shift;
    return keys | binary;
}

void runDijkstra(int dist, int x, int y) {
    if (x < 0 || y < 0) {
        return;
    }

    if (x >= COLS || y >= ROWS) {
        return;
    }

    if (map[y][x] == '#') {
        return;
    }

    if (dijkstraMap[y][x] != -1 && dijkstraMap[y][x] < dist) {
        return;
    }

    dijkstraMap[y][x] = dist;
    
    runDijkstra(dist + 1, x, y + 1);
    runDijkstra(dist + 1, x, y - 1);
    runDijkstra(dist + 1, x - 1, y);
    runDijkstra(dist + 1, x + 1, y);
}

void resetDijkstra() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            dijkstraMap[y][x] = -1;
        }
    }
}

void findAllDests(Source* target) {
    Source* dummy = newSource('\0', -1, -1);
    target->destHead = newDest(dummy, -1, -1);

    Source* currSrc = sourceHead;
    Dest* currDest = target->destHead;

    resetDijkstra();
    runDijkstra(0, target->x, target->y);

    while (currSrc != NULL) {
        if (currSrc->label == target->label || currSrc->label == '@') {
            currSrc = currSrc->next;
            continue;
        }

        currDest->next = newDest(
            currSrc,
            dijkstraMap[currSrc->y][currSrc->x],
            findDoors(currSrc->x, currSrc->y, 0)
        );
        currDest = currDest->next;
        
        currSrc = currSrc->next;
    }

    target->destHead = target->destHead->next;
}

int findDoors(int startX, int startY, int doors) {
    if (map[startY][startX] >= 'A' && map[startY][startX] <= 'Z') {
        doors = addDoor(map[startY][startX], doors);
    }

    if (dijkstraMap[startY][startX] == 0) {
        return doors;
    }

    if (dijkstraMap[startY + 1][startX] == dijkstraMap[startY][startX] - 1) {
        return findDoors(startX, startY + 1, doors);
    } else if (dijkstraMap[startY - 1][startX] == dijkstraMap[startY][startX] - 1) {
        return findDoors(startX, startY - 1, doors);
    } else if (dijkstraMap[startY][startX - 1] == dijkstraMap[startY][startX] - 1) {
        return findDoors(startX - 1, startY, doors);
    } else if (dijkstraMap[startY][startX + 1] == dijkstraMap[startY][startX] - 1) {
        return findDoors(startX + 1, startY, doors);
    }

    printf("unable to find a good path to start\n");
    exit(1);
}

void readInput(char* filename) {
    Source* current = sourceHead;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    char space;
    int x = 0;
    int y = 0;
    while (1) {
        space = fgetc(file);
        
        if (space == EOF) {
            break;
        }

        if (space == '\n') {
            x = 0;
            y++;
            continue;
        }

        if (space == '@') {
            current->next = newSource(space, x, y);
            current = current->next;
        }

        if (space >= 'a' && space <= 'z') {
            current->next = newSource(space, x, y);
            current = current->next;
        }

        map[y][x] = space;
        x++;
    }

    sourceHead = sourceHead->next;
    fclose(file);
}

void initGlobals() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS + 1; x++) {
            map[y][x] = '\0';
        }
    }

    sourceHead = newSource('\0', -1, -1);
    allKeys = 0;
}

Dest* newDest(Source* source, int dist, int doors) {
    Dest* dest = malloc(sizeof(Dest));
    
    dest->dist = dist;
    dest->next = NULL;
    dest->source = source;
    dest->doors = doors;

    return dest;
}

Source* newSource(char label, int x, int y) {
    Source* source = malloc(sizeof(Source));

    source->label = label;
    source->x = x;
    source->y = y;

    source->destHead = NULL;
    source->next = NULL;

    return source;
}
