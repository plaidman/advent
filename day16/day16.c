#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readInput(char*);
int getMultiplier(int, int);

int main(int argc, char const *argv[]) {
    char* input = readInput("input.txt");
    printf("input %s\n", input);


    int inputPos = 0;
    int multiplier = 0;
    while (1) {
        multiplier = getMultiplier(inputPos, 2);
        printf("multiplier %d %d\n", inputPos, multiplier);
        getchar();
        inputPos++;
    }

    exit(0);
}

int getMultiplier(int inputPos, int outputPos) {
    int basePattern[4] = { 0, 1, 0, -1 };
    int patternPos = (inputPos + 1) / (outputPos + 1);

    return basePattern[patternPos % 4];
}

char* readInput(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    char* input = NULL;
    size_t len = 0;
    ssize_t read = getline(&input, &len, file);
    if (read == -1) {
        printf("pageFile not read");
        exit(1);
    }

    return input;
}