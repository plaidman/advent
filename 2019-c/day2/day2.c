#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile();
char* readMemory(FILE*);
int countMemory(char*);
int* createMemory(char*, int);
int* copyMemory(int*, int);
void addCommand(int*, int);
void multiplyCommand(int*, int);
int processInstruction(int*, int*);
int runProgram(int*, int);

int main(int argc, char const *argv[]) {
    FILE* fp = openFile();
    char* line = readMemory(fp);
    int memoryCount = countMemory(line);
    int* memory = createMemory(line, memoryCount);

    for (int noun = 0; noun < 100; noun++) {
        for (int verb = 0; verb < 100; verb++) {
            int* copy = copyMemory(memory, memoryCount);

            copy[1] = noun;
            copy[2] = verb;

            int result = runProgram(copy, memoryCount);
            free(copy);

            if (result == 19690720) {
                printf("noun: %d verb: %d\n", noun, verb);
                verb = 100;
                noun = 100;
            }
        }
    }

    free(memory);
    exit(0);
}

FILE* openFile() {
    FILE* fp = fopen("day2input.txt", "r");

    if (fp == NULL) {
        printf("file not found\n");
        exit(1);
    }

    return fp;
}

char* readMemory(FILE* fp) {
    char* line;
    size_t len;
    ssize_t read;

    read = getline(&line, &len, fp);
    if (read == -1) {
        printf("line not read");
        exit(1);
    }

    fclose(fp);

    return line;
}

int countMemory(char* commands) {
    int length = strlen(commands);
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (commands[i] == ',') {
            count++;
        }
    }

    return count + 1;
}

int* createMemory(char* line, int memoryCount) {
    int* memory = malloc(sizeof(int) * memoryCount);
    char* item = strtok(line, ",");
    int count = 0;

    while (item != NULL) {
        memory[count] = atoi(item);
        count++;

        item = strtok(NULL, ",");
    }
    
    if (count != memoryCount) {
        printf("could not reconcile number of memory addresses");
        exit(0);
    }

    return memory;
}

int* copyMemory(int* memory, int memoryCount) {
    int* copy = malloc(sizeof(int) * memoryCount);

    for (int i = 0; i < memoryCount; i++) {
        copy[i] = memory[i];
    }

    return copy;
}

void addCommand(int* memory, int ip) {
    int firstAddress = memory[ip+1];
    int secondAddress = memory[ip+2];
    int storeAddress = memory[ip+3];

    memory[storeAddress] = memory[firstAddress] + memory[secondAddress];
}

void multiplyCommand(int* memory, int ip) {
    int firstAddress = memory[ip+1];
    int secondAddress = memory[ip+2];
    int storeAddress = memory[ip+3];

    memory[storeAddress] = memory[firstAddress] * memory[secondAddress];
}

int processInstruction(int* memory, int* ip) {
    int opcode = memory[*ip];

    switch (opcode) {
        case 1:
            addCommand(memory, *ip);
            *ip += 4;
            return 0;

        case 2:
            multiplyCommand(memory, *ip);
            *ip += 4;
            return 0;
        
        case 99:
            return 1;

        default:
            printf("unknown opcode: %d\n", opcode);
            return 1;
    }

    *ip += 1;
    return 0;
}

int runProgram(int* memory, int memoryCount) {
    int halt = 0;
    int ip = 0;

    while (halt == 0) {
        // getchar();
        halt = processInstruction(memory, &ip);

        if (ip >= memoryCount) {
            printf("out of bounds error");
            halt = 1;
        }
    }

    return memory[0];
}

