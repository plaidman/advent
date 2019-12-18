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

#define ROWS 3
#define COLS 9

void readInput(char*);
void initGlobals();
Source* newSource(char, int, int);
Dest* newDest(Source*, int, int);
void findAllDests(Source*);
int addDoor(char, int);
int addKey(char, int);
int isBlocked(int, int);

char map[ROWS][COLS+1];
Source* sourceHead;

int main(int argc, char const *argv[]) {
    initGlobals();
    readInput("smallest.txt");

    for(int y = 0; y < ROWS; y++) {
        printf("%s\n", map[y]);
    }

    Source* currSrc = sourceHead;
    Dest* currDest;
    while (currSrc != NULL) {
        findAllDests(currSrc);

        printf("%c %d %d\n", currSrc->label, currSrc->x, currSrc->y);

        currDest = currSrc->destHead;
        while (currDest != NULL) {
            printf("  %c\n", currDest->source->label);
            currDest = currDest->next;
        }

        currSrc = currSrc->next;
    }

    exit(0);
}

int isBlocked(int doors, int keys) {
    if ((keys | doors) == keys) {
        return 0;
    }

    return 1;
}

int addDoor(char door, int initial) {
    int shift = door - 'A';
    int binary = 1 << shift;
    return initial | binary;
}

int addKey(char key, int initial) {
    int shift = key - 'a';
    int binary = 1 << shift;
    return initial | binary;
}

// void findAllDests(Source* target) {
//     Source* dummy = newSource('\0', -1, -1);
//     target->destHead = newDest(dummy, -1);

//     Source* currSrc = sourceHead;
//     Dest* currDest = target->destHead;

//     while (currSrc != NULL) {
//         if (currSrc->label == target->label || currSrc->label == '@') {
//             currSrc = currSrc->next;
//             continue;
//         }

//         currDest->next = newDest(currSrc);
//         currDest = currDest->next;
        
//         currSrc = currSrc->next;
//     }

//     target->destHead = target->destHead->next;
// }

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
}

Dest* newDest(Source* source, int dist, int doors) {
    Dest* dest = malloc(sizeof(Dest));
    
    dest->dist = dist;
    dest->next = NULL;
    dest->source = source;
    dest->doors = 0;

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
