#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

char* readPageFile(char*);
int countMemory(char*);
Memwidth* populateMemory(char*, Memwidth);

Computer* bootup(char* filename) {
    Computer* comp = malloc(sizeof(Computer));

    char* pageFile = readPageFile(filename);
    comp->memorySize = countMemory(pageFile);
    comp->memory = populateMemory(pageFile, comp->memorySize);

    comp->instructionPointer = 0;
    comp->haltCode = -1;
    comp->output = NULL;
    comp->input = NULL;
    comp->relBase = 0;

    return comp;
}

Computer* copyComputer(Computer* comp) {
    Computer* new = malloc(sizeof(Computer));

    new->instructionPointer = 0;
    new->haltCode = -1;
    new->output = NULL;
    new->input = NULL;
    new->relBase = 0;
    new->memorySize = comp->memorySize;

    Memwidth* memory = malloc(sizeof(Memwidth) * new->memorySize);
    memcpy(memory, comp->memory, sizeof(Memwidth) * new->memorySize);
    new->memory = memory;

    return new;
}

char* readPageFile(char* filename) {
    char* pageFile = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* file = fopen(filename, "r");
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

Memwidth* populateMemory(char* pageFile, Memwidth memSize) {
    Memwidth* memory = malloc(sizeof(Memwidth) * memSize);
    char* item = strtok(pageFile, ",");
    Memwidth count = 0;

    while (item != NULL) {
        // printf("%s\n", item);
        memory[count] = atoll(item);
        count++;

        item = strtok(NULL, ",");
    }
    
    if (count != memSize) {
        printf("could not reconcile number of memory addresses\n");
        exit(1);
    }

    return memory;
}
