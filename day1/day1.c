#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int total = 0;
    int current = 0;

    fp = fopen("day1input.txt", "r");
    if (fp == NULL) {
        printf("not found");
        exit(1);
    }

    while (1) {
        read = getline(&line, &len, fp);

        if (read == -1) {
            break;
        }

        current = atoi(line);

        while (1) {
            current = current / 3 - 2;

            if (current <= 0) {
                break;
            }

            total += current;
        }
    }

    printf("total: %d\n", total);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(0);
}
