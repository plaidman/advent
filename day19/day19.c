#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

int tossDrone(Computer*, int, int);
int fitsSquare(Computer*, int, int);

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");
    Computer* copy;

    int count = 0;
    for (int y = 0; y < 50; y++) {
        for (int x = 0; x < 50; x++) {
            copy = copyComputer(comp);

            if (tossDrone(copy, x, y) == 1) {
                printf("#");
                count++;
            } else {
                printf(".");
            }
        }
        printf(" %d\n", y);
    }
    printf("count: %d\n\n", count);

    int x = 100;
    int y = 100;
    int foundX = 0;
    int halt = 0;
    int result = 0;
    while (1) {
        copy = copyComputer(comp);
        result = tossDrone(copy, x, y);

        if (result == 1) {
            foundX = 1;

            if (fitsSquare(comp, x, y) == 1) {
                break;
            }
        }

        if (result == 0 && foundX == 1) {
            y++;
            x = 0;
            foundX = 0;
            continue;
        }
        
        x++;
    }

    printf("x %d\ny %d\n", x, y);
}

int fitsSquare(Computer* comp, int x, int y) {
    Computer* copy;

    for (int i = 0; i < 100; i++) {
        copy = copyComputer(comp);
        if (tossDrone(copy, x + i, y) == 0) return 0;

        copy = copyComputer(comp);
        if (tossDrone(copy, x, y + i) == 0) return 0;
    }

    return 1;
}

int tossDrone(Computer* comp, int x, int y) {
    pushMessage(&(comp->input), x);
    pushMessage(&(comp->input), y);

    runProgram(comp);

    return popMessage(&(comp->output));
}