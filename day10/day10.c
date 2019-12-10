#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define asteroid struct asteroid
asteroid {
    int x;
    int y;
    int othersVisible;

    asteroid* next;
};

void readInput(char*);

int main(int argc, char const *argv[]) {
    readInput("input.txt");

    return 0;
}

void readInput(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    char space = 'X';
    int x = 0;
    int y = 0;
    while (1) {
        space = fgetc(file);
        
        if (space == EOF) {
            printf("\n");
            break;
        }

        if (space == '\n') {
            x = 0;
            y++;
            continue;
        }

        if (space == '#') {
            printf("asteroid %d %d\n", x, y);
        }

        x++;
    }

    fclose(file);
}
