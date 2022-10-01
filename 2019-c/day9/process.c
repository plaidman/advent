#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "messages.h"

instruction parseInstruction(memwidth);
void executeInstruction(computer*);

void opAdd(computer*, instruction);
void opMultiply(computer*, instruction);
void opInput(computer*, instruction);
void opOutput(computer*, instruction);
void opJumpIfTrue(computer*, instruction);
void opJumpIfFalse(computer*, instruction);
void opLessThan(computer*, instruction);
void opEqualTo(computer*, instruction);
void opAdjustBase(computer*, instruction);

memwidth resolveParamValue(computer*, memwidth, int);
memwidth resolveStoreAddress(computer*, memwidth, int);
void growMemory(computer*, memwidth);

void runProgram(computer* comp) {
    comp->haltCode = 0;

    while (comp->haltCode == 0) {
        executeInstruction(comp);

        if (comp->instructionPointer >= comp->memorySize) {
            printf("instruction out of bounds\n");
            exit(1);
        }
    }
}

instruction parseInstruction(memwidth memValue) {
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

        case 9:
            opAdjustBase(comp, inst);
            break;
        
        case 99:
            printf("done\n");
            comp->haltCode = 99;
            break;

        default:
            printf("unknown opcode: %d\n", inst.opCode);
            exit(1);
    }
}

void opAdd(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;

    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    comp->memory[storeParam] = firstParam + secondParam;

    comp->instructionPointer += 4;
}

void opMultiply(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    comp->memory[storeParam] = firstParam * secondParam;

    comp->instructionPointer += 4;
}

void opInput(computer* comp, instruction inst) {
    if (hasMessages(comp->input) == 0) {
        printf("halting for input at address %lld\n", comp->instructionPointer);
        comp->haltCode = 3;
        return;
    }

    memwidth ip = comp->instructionPointer;
    memwidth storeParam = resolveStoreAddress(comp, ip+1, inst.paramAMode);

    memwidth value = popMessage(&(comp->input));

    printf("input at address %lld: %lld\n", ip, value);
    comp->memory[storeParam] = value;
    comp->instructionPointer += 2;
}

void opOutput(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);

    printf("output at address %lld: %lld\n", ip, firstParam);
    pushMessage(&(comp->output), firstParam);
    comp->instructionPointer += 2;
}

void opJumpIfTrue(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam != 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opJumpIfFalse(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam == 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opLessThan(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    if (firstParam < secondParam) {
        comp->memory[storeParam] = 1;
    } else {
        comp->memory[storeParam] = 0;
    }

    comp->instructionPointer += 4;
}

void opEqualTo(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    if (firstParam == secondParam) {
        comp->memory[storeParam] = 1;
    } else {
        comp->memory[storeParam] = 0;
    }

    comp->instructionPointer += 4;
}

void opAdjustBase(computer* comp, instruction inst) {
    memwidth ip = comp->instructionPointer;
    memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);

    comp->relBase += firstParam;

    comp->instructionPointer += 2;
}

memwidth resolveParamValue(computer* comp, memwidth address, int mode) {
    memwidth value = comp->memory[address];

    switch (mode) {
        case 0:
            growMemory(comp, value);
            return comp->memory[value];
        
        case 1:
            return value;

        case 2:
            growMemory(comp, comp->relBase + value);
            return comp->memory[comp->relBase + value];

        default:
            printf("invalid mode: %d\n", mode);
            exit(1);
    }
}

memwidth resolveStoreAddress(computer* comp, memwidth address, int paramMode) {
    switch (paramMode) {
        case 0:
            growMemory(comp, comp->memory[address]);
            return comp->memory[address];
        
        case 2:
            growMemory(comp, comp->relBase + comp->memory[address]);
            return comp->relBase + comp->memory[address];

        default:
            printf("invalid mode: %d\n", paramMode);
            exit(1);
    }
}

void growMemory(computer* comp, memwidth address) {
    if (comp->memorySize > address) {
        return;
    }

    address += 100;
    printf("growing memory from %lld to %lld\n", comp->memorySize, address);

    memwidth* newMemory = malloc(sizeof(memwidth) * address);
    for (memwidth i = 0; i < address; i++) {
        newMemory[i] = 0;
    }

    memcpy(newMemory, comp->memory, sizeof(memwidth) * comp->memorySize);

    comp->memory = newMemory;
    comp->memorySize = address;

    // for (memwidth i = 0; i < address; i++) {
    //     printf("new memory %d\n", comp->memory[i]);
    // }
}
