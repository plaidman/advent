#include <stdio.h>
#include <stdlib.h>

#include "process.h"

#define instruction struct instruction

instruction {
    int opCode;
    int paramAMode;
    int paramBMode;
    int paramCMode;
};

instruction parseInstruction(int);
int executeInstruction(int*, int*);

void add(int*, int*, instruction);
void multiply(int*, int*, instruction);
void input(int*, int*, instruction);
void output(int*, int*, instruction);
void jumpIfTrue(int*, int*, instruction);
void jumpIfFalse(int*, int*, instruction);
void lessThan(int*, int*, instruction);
void equalTo(int*, int*, instruction);

int resolveParamValue(int, int, int*);

void runProgram(int* memory, int memoryCount) {
    int halt = 0;
    int ip = 0;

    while (halt == 0) {
        halt = executeInstruction(memory, &ip);

        if (ip >= memoryCount) {
            printf("ip out of bounds\n");
            halt = 1;
        }
    }

    printf("done\n\n");
}

instruction parseInstruction(int memValue) {
    instruction inst;

    inst.opCode = memValue % 100;
    memValue /= 100;

    inst.paramAMode = memValue % 10;
    memValue /= 10;

    inst.paramBMode = memValue % 10;
    memValue /= 10;

    inst.paramCMode = memValue % 10;

    return inst;
}

int executeInstruction(int* memory, int* ip) {
    instruction inst = parseInstruction(memory[*ip]);

    switch (inst.opCode) {
        case 1:
            add(memory, ip, inst);
            return 0;

        case 2:
            multiply(memory, ip, inst);
            return 0;

        case 3:
            input(memory, ip, inst);
            return 0;

        case 4:
            output(memory, ip, inst);
            return 0;
        
        case 5:
            jumpIfTrue(memory, ip, inst);
            return 0;
        
        case 6:
            jumpIfFalse(memory, ip, inst);
            return 0;
        
        case 7:
            lessThan(memory, ip, inst);
            return 0;
        
        case 8:
            equalTo(memory, ip, inst);
            return 0;
        
        case 99:
            return 1;

        default:
            printf("unknown opcode: %d\n", inst.opCode);
            exit(1);
    }
}

void add(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);
    int storeParam = memory[*ip+3];

    memory[storeParam] = firstParam + secondParam;

    *ip += 4;
}

void input(int* memory, int* ip, instruction inst) {
    int storeAddress = memory[*ip+1];
    int input;

    printf("input at address %d: ", *ip);
    scanf("%d", &input);
    memory[storeAddress] = input;

    *ip += 2;
}

void output(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);

    printf("output at address %d: %d\n", *ip, firstParam);

    *ip += 2;
}

void multiply(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);
    int storeAddress = memory[*ip+3];

    memory[storeAddress] = firstParam * secondParam;

    *ip += 4;
}

void jumpIfTrue(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);

    if (firstParam != 0) {
        *ip = secondParam;
    } else {
        *ip += 3;
    }
}

void jumpIfFalse(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);

    if (firstParam == 0) {
        *ip = secondParam;
    } else {
        *ip += 3;
    }
}

void lessThan(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);
    int storeAddress = memory[*ip+3];

    if (firstParam < secondParam) {
        memory[storeAddress] = 1;
    } else {
        memory[storeAddress] = 0;
    }

    *ip += 4;
}

void equalTo(int* memory, int* ip, instruction inst) {
    int firstParam = resolveParamValue(inst.paramAMode, memory[*ip+1], memory);
    int secondParam = resolveParamValue(inst.paramBMode, memory[*ip+2], memory);
    int storeAddress = memory[*ip+3];

    if (firstParam == secondParam) {
        memory[storeAddress] = 1;
    } else {
        memory[storeAddress] = 0;
    }

    *ip += 4;
}

int resolveParamValue(int mode, int value, int* memory) {
    switch (mode) {
        case 0:
            return memory[value];
        
        case 1:
            return value;

        default:
            printf("invalid mode: %d\n", mode);
            exit(1);
    }
}
