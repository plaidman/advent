#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define layer struct layer
layer {
    char string[151];
    layer* next;
};

char* readInput(char*);
layer* createLayer(char*);
int calculateChecksum(layer*);
char* combineStrings(layer*);

int main(int argc, char const *argv[]) {
    char* input = readInput("input.txt");
    layer* head = createLayer("temp");
    layer* current = head;

    for (int i = 0; i < 100; i++) {
        current->next = createLayer(input);
        current = current->next;
        input = input+150;
    }

    head = head->next;
    int checksum = calculateChecksum(head);
    printf("checksum %d\n", checksum);

    char* combined = combineStrings(head);
    printf("\n%s\n", combined);

    return 0;
}

char* combineStrings(layer* head) {
    layer* current = head;
    char* combined = malloc(sizeof(char) * 151);

    for (int i = 0; i < 150; i++) {
        while (current->string[i] == '2' && current != NULL) {
            current = current->next;
        }

        if (current == NULL) {
            combined[i] = '2';
        } else {
            combined[i] = current->string[i];
        }

        current = head;
    }

    combined[150] = '\0';
    return combined;
}

int calculateChecksum(layer* head) {
    layer* current = head;

    int minZero = 99999;
    int checksum = 0;
    int digitCounts[3];

    while (current != NULL) {
        // printf("%s\n", current->string);

        for (int i = 0; i < 3; i++) {
            digitCounts[i] = 0;
        }

        for (int i = 0; i < 150; i++) {
            int digit = current->string[i] - '0';
            digitCounts[digit]++;
        }

        if (digitCounts[0] < minZero) {
            minZero = digitCounts[0];
            checksum = digitCounts[1] * digitCounts[2];
        }

        current = current->next;
    }

    return checksum;
}

layer* createLayer(char* string) {
    layer* l = malloc(sizeof(layer));
    l->next = NULL;

    memcpy(l->string, string, sizeof(char) * 150);
    l->string[150] = '\0';

    return l;
}

char* readInput(char* filename) {
    char* input = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    read = getline(&input, &len, file);
    if (read == -1) {
        printf("input not read");
        exit(1);
    }

    fclose(file);
    return input;
}
