#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readPageFile();
int countMemory(char*);
int* populateMemory(char*, int);

void bootup(int** memory, int* memSize) {
    char* pageFile = readPageFile();
    *memSize = countMemory(pageFile);
    *memory = populateMemory(pageFile, *memSize);
}

char* readPageFile() {
    char* pageFile = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    read = getline(&pageFile, &len, file);
    if (read == -1) {
        printf("pageFile not read");
        exit(1);
    }

    fclose(file);
    return pageFile;
}

int countMemory(char* pageFile) {
    int length = strlen(pageFile);
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (pageFile[i] == ',') {
            count++;
        }
    }

    return count + 1;
}

int* populateMemory(char* pageFile, int memSize) {
    int* memory = malloc(sizeof(int) * memSize);
    char* item = strtok(pageFile, ",");
    int count = 0;

    while (item != NULL) {
        memory[count] = atoi(item);
        count++;

        item = strtok(NULL, ",");
    }
    
    if (count != memSize) {
        printf("could not reconcile number of memory addresses\n");
        exit(1);
    }

    return memory;
}
