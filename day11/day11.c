#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

#define GridSpace struct GridSpace
GridSpace {
    int x;
    int y;
    int painted;
    int color;
    GridSpace* next;
};

#define Robot struct Robot
Robot {
    int x;
    int y;
    int direction; // 0 = up; 1 = right; 2 = down; 3 = left;
};

Robot* createRobot();
GridSpace* createGridSpace(int, int);
void pushGridSpace(GridSpace*, GridSpace*);
GridSpace* findGridSpace(GridSpace*, int, int);
void turnRobot(Robot*, int);
void calculateGridOffset(GridSpace*);
void drawGrid(GridSpace*);

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");
    Robot* robot = createRobot();
    GridSpace* grid = createGridSpace(0, 0);
    grid->color = 1;
    GridSpace* current;

    while (1) {
        current = findGridSpace(grid, robot->x, robot->y);
        if (current == NULL) {
            current = createGridSpace(robot->x, robot->y);
            pushGridSpace(grid, current);
        }

        pushMessage(&(comp->input), current->color);
        runProgram(comp);

        int color = popMessage(&(comp->output));
        int direction = popMessage(&(comp->output));

        current->color = color;
        current->painted = 1;
        turnRobot(robot, direction);

        if (comp->haltCode == 99) {
            printf("\nprocessing image\n\n");
            break;
        }
    }

    current = grid;
    int spaces = 0;
    while (current != NULL) {
        // printf("found %d, %d\n", current->x, current->y);
        spaces += current->painted;
        current = current->next;
    }
    printf("%d spaces painted\n\n", spaces);

    calculateGridOffset(grid);
    // current = grid;
    // while (current != NULL) {
    //     printf("found %d, %d\n", current->x, current->y);
    //     current = current->next;
    // }

    drawGrid(grid);

    exit(0);
}

void drawGrid(GridSpace* grid) {
    GridSpace* current = grid;

    int maxX = 0;
    int maxY = 0;
    while (current != NULL) {
        if (current->x > maxX) maxX = current->x;
        if (current->y > maxY) maxY = current->y;
        
        current = current->next;
    }

    printf("max %d, %d\n\n", maxX, maxY);

    char output[maxY+1][maxX+2];
    for (int i = 0; i < maxY+1; i++) {
        for (int j = 0; j < maxX+1; j++) {
            output[i][j] = ' ';
        }

        output[i][maxX+1] = '\0';
    }

    current = grid;
    while (current != NULL) {
        if (current->color == 1) {
            output[current->y][current->x] = '#';
        }
        
        current = current->next;
    }

    for (int i = 0; i < maxY+1; i++) {
        printf("%s\n", output[i]);
    }
}

void calculateGridOffset(GridSpace* grid) {
    GridSpace* current = grid;

    int minX = 99999;
    int minY = 99999;
    while (current != NULL) {
        if (current->x < minX) minX = current->x;
        if (current->y < minY) minY = current->y;
        
        current = current->next;
    }

    current = grid;
    while (current != NULL) {
        current->x -= minX;
        current->y -= minY;
        
        current = current->next;
    }
}

Robot* createRobot() {
    Robot* robot = malloc(sizeof(Robot));

    robot->x = 0;
    robot->y = 0;
    robot->direction = 0;

    return robot;
}


GridSpace* createGridSpace(int x, int y) {
    GridSpace* space = malloc(sizeof(GridSpace));

    space->x = x;
    space->y = y;
    space->painted = 0;
    space->color = 0;
    space->next = 0;

    return space;
}

void pushGridSpace(GridSpace* grid, GridSpace* subject) {
    GridSpace* current = grid;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = subject;
}

GridSpace* findGridSpace(GridSpace* grid, int x, int y) {
    GridSpace* current = grid;

    while (current != NULL) {
        if (current->x == x && current->y == y) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void turnRobot(Robot* robot, int direction) {
    switch (direction) {
        case 0:
            robot->direction -= 1;
            if (robot->direction < 0) robot->direction += 4;
            break;

        case 1:
            robot->direction += 1;
            if (robot->direction > 3) robot->direction -= 4;
            break;

        default:
            printf("unknown input direction: %d", direction);
            exit(1);
    }

    switch (robot->direction) {
        case 0: // up, but really subtract since we're building the grid top down
            robot->y -= 1;
            break;

        case 1: // right
            robot->x += 1;
            break;

        case 2: // down
            robot->y += 1;
            break;

        case 3: // left
            robot->x -= 1;
            break;

        default:
            printf("unknown robot direction: %d", robot->direction);
            exit(1);
    }
}
