#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int validate(char*);
int sixDigit(char*);
int twoAdjacent(char*);
int neverDecrease(char*);
int adjacentLookahead(char*);

int main(int argc, char const *argv[]) {
    int lower = 206938;
    int upper = 679128;
    char curString[10];
    int count = 0;

    for (int i = lower; i < upper + 1; i++) {
        sprintf(curString, "%d", i);

        if (validate(curString) == 1) {
            count++;
        }
    }

    printf("%d\n", count);

    exit(0);
}

int validate(char* number) {
    if (sixDigit(number) == 0) {
        return 0;
    }

    if (neverDecrease(number) == 0) {
        return 0;
    }

    if (twoAdjacent(number) == 0) {
        return 0;
    }

    return 1;
}

int sixDigit(char* number) {
    return strlen(number) == 6;
}

int neverDecrease(char* number) {
    for (int i = 0; i < strlen(number) - 1; i++) {
        if (number[i + 1] < number[i]) {
            return 0;
        }
    }

    return 1;
}

int twoAdjacent(char* number) {
    int current = 0;
    int count;

    while (current < strlen(number)) {
        count = adjacentLookahead(number + (sizeof(char) * current));

        if (count == 2) {
            return 1;
        }

        current += count;
    }

    return 0;
}

int adjacentLookahead(char* number) {
    int current = 0;

    while (number[0] == number[current]) {
        current++;
    }

    return current;
}
