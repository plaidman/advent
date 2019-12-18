#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

#define NUM_LINES 49
#define LINE_LEN 57

int isIntersected(char** map, int x, int y);
int isOnEdge(int x, int y);
void printMap(Computer* comp);

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");
    runProgram(comp);
    printMap(comp);
    free(comp);

    /*
    full = L,12,L,8,R,12,L,10,L,8,L,12,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,12,L,8,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12,

    ^(.{1,21})\1*(.{1,21})(?:\1|\2)*(.{1,21})(?:\1|\2|\3)*$
    magic.gif

    A = L,12,L,8,R,12
    B = L,10,L,8,L,12,R,12
    C = R,12,L,8,L,10
    X = A,B,A,C,A,A,C,B,C,B
    */

    comp = bootup("input.txt");
    comp->memory[0] = 2;

    char* input = "A,B,A,C,A,A,C,B,C,B\nL,12,L,8,R,12\nL,10,L,8,L,12,R,12\nR,12,L,8,L,10\nn\n";
    for (int i = 0; i < strlen(input); i++) {
        pushMessage(&(comp->input), input[i]);
    }

    runProgram(comp);

    Memwidth dust;
    while (hasMessages(comp->output)) {
        dust = popMessage(&(comp->output));
    }
    printf("\n%llu dust\n", dust);

    exit(0);
}

void printMap(Computer* comp) {
    char* map[NUM_LINES];
    for (int i = 0; i < NUM_LINES; i++) {
        map[i] = NULL;
    }
    map[0] = malloc((sizeof(char) * LINE_LEN) + 1);
    map[0][0] = '\0';

    int count = 0;
    int line = 0;
    while (hasMessages(comp->output)) {
        char output = popMessage(&(comp->output));

        if (output == '\n') {
            map[line][count] = '\0';
            count = 0;
            line++;

            if (line >= NUM_LINES) {
                break;
            }

            map[line] = malloc(sizeof(char) * LINE_LEN);
            map[line][0] = '\0';

            continue;
        }

        map[line][count] = output;
        count++;
    }

    int total = 0;
    for (int y = 0; y < NUM_LINES; y++) {
        for (int x = 0; x < LINE_LEN; x++) {
            if (isIntersected(map, x, y) == 1) {
                map[y][x] = '+';
                total += (x * y);
            }
        }
    }

    for (int i = 0; i < NUM_LINES; i++) {
        printf("%s %d\n", map[i], i);
    }

    printf("\nsum: %d\n\n", total);
}

int isOnEdge(int x, int y) {
    if (x == 0 || y == 0) {
        return 1;
    }

    if (x >= LINE_LEN - 1 || y >= NUM_LINES - 1) {
        return 1;
    }

    return 0;
}

int isIntersected(char** map, int x, int y) {
    if (isOnEdge(x, y)) {
        return 0;
    }

    char up = map[y+1][x];
    char down = map[y-1][x];
    char left = map[y][x-1];
    char right = map[y][x+1];

    if (up == '#' && down == '#' && left == '#' && right == '#') {
        return 1;
    }

    return 0;
}
