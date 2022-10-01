#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lli long long int
#define llu long long unsigned int

char* readInput(char*);
int getMultiplier(int, int);
char* substring(char*, int, int);
char* calculatePartOne(char*);
char* calculatePartTwo(char*);

int main(int argc, char const *argv[]) {
    char* input = readInput("input.txt");
    char* output = calculatePartOne(input);
    printf("part one: %s\n\n", substring(output, 0, 8));

    // for this we really only care about the 2nd half of the thing
    //  don't bother taking the full 10k iterations
    input = readInput("input.txt");
    int len = strlen(input);
    int fullLen = strlen(input) * 5000;
    char* fullInput = malloc((sizeof(char) * fullLen) + 1);

    printf("building string for part two\n");
    for (int i = 0; i < fullLen; i++) {
        fullInput[i] = input[i % len];
    }
    fullInput[fullLen] = '\0';

    int offset = atoi(substring(input, 0, 7));
    // adjust because we only took the 2nd half of the input
    offset -= fullLen;
    output = calculatePartTwo(fullInput + offset);
    printf("part two: %s.\n", output);

    exit(0);
}

//6170604007
char* calculatePartTwo(char* input) {
    int length = strlen(input);
    llu total;

    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < length; i++) {
            if (i % 1000 == 0) {
                printf("%d iteration, %d%% complete\n", k, i * 100 / length);
            }

            total = 0;

            for (int j = i; j < length; j++) {
                total += input[j] - '0';
            }

            input[i] = (total % 10) + '0';
        }
    }

    input[8] = '\0';
    return input;
}

char* calculatePartOne(char* input) {
    int length = strlen(input);
    char* output = malloc((sizeof(char) * length) + 1);
    output[length] = '\0';
    int total;

    for (int k = 0; k < 100; k++) {
        for (int j = 0; j < length; j++) {
            total = 0;

            for (int i = 0; i < length; i++) {
                int digit = input[i] - '0';
                total += digit * getMultiplier(i, j);
            }

            output[j] = (abs(total) % 10) + '0';
        }

        input = output;
    }

    return output;
}

char* substring(char* input, int start, int count) {
    char* output = malloc(sizeof(char) * count + 1);
    for (int i = 0; i < count; i++) {
        output[i] = input[start + i];
    }
    output[count] = '\0';


    return output;
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