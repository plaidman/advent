#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define WALL 0
#define FLOOR 1
#define OX_SYS 2

#define Cell struct Cell
Cell {
    int type;
    int distance;
    Cell** directions;
    int prevDir;
};

void populateCell(Cell*, Computer*, Cell**);
void populateDirection(Cell*, Computer*, Cell**, int, int);
Memwidth tryDirection(Computer*, int);
Cell* newCell(int);
void printCell(Cell*);
void distanceCell(Cell*, int, Cell**);

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");
    Cell* grid = newCell(FLOOR);
    Cell* current = grid;
    Cell* oxygen = NULL;
    Cell* maxDist = grid;

    populateCell(current, comp, &oxygen);

    if (oxygen == NULL) {
        printf("oxygen not found\n");
        exit(1);
    }

    distanceCell(oxygen, 0, &maxDist);
    printf("distance to start %d\n", grid->distance);
    printf("distance to last %d\n", maxDist->distance);
    
    exit(0);
}

void distanceCell(Cell* current, int distance, Cell** maxDist) {
    if (current->type == WALL) {
        return;
    }


    if (current->distance != -1 && current->distance <= distance) {
        return;
    }

    if ((*maxDist)->distance < distance) {
        *maxDist = current;
    }

    current->distance = distance;

    distanceCell(current->directions[UP], distance + 1, maxDist);
    distanceCell(current->directions[DOWN], distance + 1, maxDist);
    distanceCell(current->directions[LEFT], distance + 1, maxDist);
    distanceCell(current->directions[RIGHT], distance + 1, maxDist);
}

void populateCell(Cell* current, Computer* comp, Cell** oxygen) {
    populateDirection(current, comp, oxygen, UP, DOWN);
    populateDirection(current, comp, oxygen, DOWN, UP);
    populateDirection(current, comp, oxygen, LEFT, RIGHT);
    populateDirection(current, comp, oxygen, RIGHT, LEFT);

    if (current->prevDir == -1) {
        return;
    }

    Memwidth result = tryDirection(comp, current->prevDir);
    if (result == WALL) {
        printf("hit unexpected wall\n");
        exit(1);
    }
}

void populateDirection(Cell* current, Computer* comp, Cell** oxygen, int forwards, int backwards) {
    if (current->directions[forwards] != NULL) {
        return;
    }

    Memwidth result = tryDirection(comp, forwards);
    Cell* new = newCell(result);

    if (result == WALL) {
        current->directions[forwards] = new;
        return;
    }

    if (result == OX_SYS) {
        if (*oxygen != NULL) {
            printf("found oxygen twice\n");
            exit(1);
        }

        *oxygen = new;
    }

    new->directions[backwards] = current;
    current->directions[forwards] = new;
    new->prevDir = backwards;

    populateCell(new, comp, oxygen);
}

void printCell(Cell* cell) {
    printf(
        "cell type: %d, up: %d, down: %d, left: %d, right %d\n",
        cell->type,
        cell->directions[UP]->type,
        cell->directions[DOWN]->type,
        cell->directions[LEFT]->type,
        cell->directions[RIGHT]->type
    );
}

Memwidth tryDirection(Computer* comp, int direction) {
    pushMessage(&(comp->input), direction+1);
    runProgram(comp);
    return popMessage(&(comp->output));
}

Cell* newCell(int type) {
    Cell* cell = malloc(sizeof(Cell));

    cell->type = type;
    cell->distance = -1;
    cell->prevDir = -1;

    cell->directions = malloc(sizeof(Cell*) * 4);
    for (int i = 0; i < 4; i++) {
        cell->directions[i] = NULL;
    }

    return cell;
}
