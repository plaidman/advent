#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "messages.h"

instruction parseInstruction(int);
void executeInstruction(computer*);

void opAdd(computer*, instruction);
void opMultiply(computer*, instruction);
void opInput(computer*, instruction);
void opOutput(computer*, instruction);
void opJumpIfTrue(computer*, instruction);
void opJumpIfFalse(computer*, instruction);
void opLessThan(computer*, instruction);
void opEqualTo(computer*, instruction);

int resolveParamValue(computer*, int, int);

void runProgram(computer* comp) {
    comp->running = 1;

    while (comp->running == 1) {
        executeInstruction(comp);

        if (comp->instructionPointer >= comp->memorySize) {
            printf("instruction out of bounds\n");
            exit(1);
        }
    }
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

void executeInstruction(computer* comp) {
    instruction inst = parseInstruction(comp->memory[comp->instructionPointer]);

    switch (inst.opCode) {
        case 1:
            opAdd(comp, inst);
            break;

        case 2:
            opMultiply(comp, inst);
            break;

        case 3:
            opInput(comp, inst);
            break;

        case 4:
            opOutput(comp, inst);
            break;
        
        case 5:
            opJumpIfTrue(comp, inst);
            break;
        
        case 6:
            opJumpIfFalse(comp, inst);
            break;
        
        case 7:
            opLessThan(comp, inst);
            break;
        
        case 8:
            opEqualTo(comp, inst);
            break;
        
        case 99:
            comp->running = 0;
            break;

        default:
            printf("unknown opcode: %d\n", inst.opCode);
            exit(1);
    }
}

void opAdd(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;

    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    int storeParam = comp->memory[ip+3];

    comp->memory[storeParam] = firstParam + secondParam;

    comp->instructionPointer += 4;
}

void opMultiply(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    int storeParam = comp->memory[ip+3];

    comp->memory[storeParam] = firstParam * secondParam;

    comp->instructionPointer += 4;
}

void opInput(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int storeAddress = comp->memory[ip+1];

    int value = comp->input[comp->inputPointer];
    comp->inputPointer++;

    printf("input at address %d: %d\n", ip, value);
    comp->memory[storeAddress] = value;
    comp->instructionPointer += 2;
}

void opOutput(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);

    printf("output at address %d: %d\n", ip, firstParam);
    pushMessage(&(comp->output), firstParam);
    comp->instructionPointer += 2;
}

void opJumpIfTrue(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam != 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opJumpIfFalse(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam == 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opLessThan(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    int storeAddress = comp->memory[ip+3];

    if (firstParam < secondParam) {
        comp->memory[storeAddress] = 1;
    } else {
        comp->memory[storeAddress] = 0;
    }

    comp->instructionPointer += 4;
}

void opEqualTo(computer* comp, instruction inst) {
    int ip = comp->instructionPointer;
    int firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    int secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    int storeAddress = comp->memory[ip+3];

    if (firstParam == secondParam) {
        comp->memory[storeAddress] = 1;
    } else {
        comp->memory[storeAddress] = 0;
    }

    comp->instructionPointer += 4;
}

int resolveParamValue(computer* comp, int address, int mode) {
    int value = comp->memory[address];

    switch (mode) {
        case 0:
            return comp->memory[value];
        
        case 1:
            return value;

        default:
            printf("invalid mode: %d\n", mode);
            exit(1);
    }
}
