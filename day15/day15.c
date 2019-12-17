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
};

void handleCell(Cell*, Computer*, Cell**);
void handleDirection(Cell*, Computer*, Cell**, int, int);
int allDirectionsKnown(Cell*);
void populateWall(Cell*, Computer*, int, int);
void populateWalls(Cell*, Computer*);
Memwidth tryDirection(Computer*, int, int);
Cell* newCell(int);

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");
    Cell* grid = newCell(FLOOR);
    Cell* current = grid;
    Cell* oxygen = NULL;

    handleCell(current, comp, &oxygen);

    if (oxygen == NULL) {
        printf("oxygen not found\n");
        exit(1);
    }
    
    exit(0);
}

void handleCell(Cell* current, Computer* comp, Cell** oxygen) {
    populateWalls(current, comp);

    while (allDirectionsKnown(current) == 1) {
        return;
    }

    handleDirection(current, comp, oxygen, UP, DOWN);
    handleDirection(current, comp, oxygen, DOWN, UP);
    handleDirection(current, comp, oxygen, LEFT, RIGHT);
    handleDirection(current, comp, oxygen, RIGHT, LEFT);
}

void handleDirection(Cell* current, Computer* comp, Cell** oxygen, int forwards, int backwards) {
    if (current->directions[forwards] != NULL) {
        Memwidth result = tryDirection(comp, forwards, 1);
        Cell* new = newCell(result);

        if (result == OX_SYS) {
            if (*oxygen == NULL) {
                printf("found oxygen twice\n");
                exit(1);
            }

            *oxygen = new;
        }

        new->directions[backwards] = current;
        current->directions[forwards] = new;

        handleCell(new, comp, oxygen);
    }
}

int allDirectionsKnown(Cell* cell) {
    for (int i = 0; i < 4; i++) {
        if (cell->directions[i] == NULL) {
            return 0;
        }
    }

    return 1;
}

void populateWall(Cell* cell, Computer* comp, int forwards, int backwards) {
    Memwidth result = tryDirection(comp, forwards, 0);

    if (result == WALL) {
        cell->directions[UP] = newCell(WALL);
    } else {
        tryDirection(comp, backwards, 1);
    }
}

void populateWalls(Cell* cell, Computer* comp) {
    populateWall(cell, comp, UP, DOWN);
    populateWall(cell, comp, DOWN, UP);
    populateWall(cell, comp, LEFT, RIGHT);
    populateWall(cell, comp, RIGHT, LEFT);
}

Memwidth tryDirection(Computer* comp, int direction, int expectsFloor) {
    pushMessage(&(comp->input), direction+1);
    runProgram(comp);
    Memwidth response = popMessage(&(comp->output));
    
    if (expectsFloor == 1 && response == WALL) {
        printf("unexpected wall where a floor was known\n");
        exit(1);
    }

    return response;
}

Cell* newCell(int type) {
    Cell* cell = malloc(sizeof(Cell));

    cell->type = type;
    cell->distance = 0;

    cell->directions = malloc(sizeof(Cell*) * 4);
    for (int i = 0; i < 4; i++) {
        cell->directions[0] = NULL;
    }

    return cell;
}
