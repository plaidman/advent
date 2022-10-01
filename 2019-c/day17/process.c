#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "messages.h"

Instruction parseInstruction(Memwidth);
void executeInstruction(Computer*);

void opAdd(Computer*, Instruction);
void opMultiply(Computer*, Instruction);
void opInput(Computer*, Instruction);
void opOutput(Computer*, Instruction);
void opJumpIfTrue(Computer*, Instruction);
void opJumpIfFalse(Computer*, Instruction);
void opLessThan(Computer*, Instruction);
void opEqualTo(Computer*, Instruction);
void opAdjustBase(Computer*, Instruction);

Memwidth resolveParamValue(Computer*, Memwidth, int);
Memwidth resolveStoreAddress(Computer*, Memwidth, int);
void growMemory(Computer*, Memwidth);

void runProgram(Computer* comp) {
    comp->haltCode = 0;

    while (comp->haltCode == 0) {
        executeInstruction(comp);

        if (comp->instructionPointer >= comp->memorySize) {
            printf("Instruction out of bounds\n");
            exit(1);
        }
    }
}

Instruction parseInstruction(Memwidth memValue) {
    Instruction inst;

    inst.opCode = memValue % 100;
    memValue /= 100;

    inst.paramAMode = memValue % 10;
    memValue /= 10;

    inst.paramBMode = memValue % 10;
    memValue /= 10;

    inst.paramCMode = memValue % 10;

    return inst;
}

void executeInstruction(Computer* comp) {
    Instruction inst = parseInstruction(comp->memory[comp->instructionPointer]);

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

void opAdd(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;

    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    Memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    comp->memory[storeParam] = firstParam + secondParam;

    comp->instructionPointer += 4;
}

void opMultiply(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    Memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    comp->memory[storeParam] = firstParam * secondParam;

    comp->instructionPointer += 4;
}

void opInput(Computer* comp, Instruction inst) {
    if (hasMessages(comp->input) == 0) {
        printf("waiting for input at address %lld\n", comp->instructionPointer);
        comp->haltCode = 3;
        return;
    }

    Memwidth ip = comp->instructionPointer;
    Memwidth storeParam = resolveStoreAddress(comp, ip+1, inst.paramAMode);

    Memwidth value = popMessage(&(comp->input));

    printf("input at address %lld: %lld\n", ip, value);
    comp->memory[storeParam] = value;
    comp->instructionPointer += 2;
}

void opOutput(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);

    printf("output at address %lld: %lld\n", ip, firstParam);
    pushMessage(&(comp->output), firstParam);
    comp->instructionPointer += 2;
}

void opJumpIfTrue(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam != 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opJumpIfFalse(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);

    if (firstParam == 0) {
        comp->instructionPointer = secondParam;
    } else {
        comp->instructionPointer += 3;
    }
}

void opLessThan(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    Memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    if (firstParam < secondParam) {
        comp->memory[storeParam] = 1;
    } else {
        comp->memory[storeParam] = 0;
    }

    comp->instructionPointer += 4;
}

void opEqualTo(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);
    Memwidth secondParam = resolveParamValue(comp, ip+2, inst.paramBMode);
    Memwidth storeParam = resolveStoreAddress(comp, ip+3, inst.paramCMode);

    if (firstParam == secondParam) {
        comp->memory[storeParam] = 1;
    } else {
        comp->memory[storeParam] = 0;
    }

    comp->instructionPointer += 4;
}

void opAdjustBase(Computer* comp, Instruction inst) {
    Memwidth ip = comp->instructionPointer;
    Memwidth firstParam = resolveParamValue(comp, ip+1, inst.paramAMode);

    comp->relBase += firstParam;

    comp->instructionPointer += 2;
}

Memwidth resolveParamValue(Computer* comp, Memwidth address, int mode) {
    Memwidth value = comp->memory[address];

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

Memwidth resolveStoreAddress(Computer* comp, Memwidth address, int paramMode) {
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

void growMemory(Computer* comp, Memwidth address) {
    if (comp->memorySize > address) {
        return;
    }

    address += 100;
    printf("growing memory from %lld to %lld\n", comp->memorySize, address);

    Memwidth* newMemory = malloc(sizeof(Memwidth) * address);
    for (Memwidth i = 0; i < address; i++) {
        newMemory[i] = 0;
    }

    memcpy(newMemory, comp->memory, sizeof(Memwidth) * comp->memorySize);

    comp->memory = newMemory;
    comp->memorySize = address;

    // for (Memwidth i = 0; i < address; i++) {
    //     printf("new memory %d\n", comp->memory[i]);
    // }
}
