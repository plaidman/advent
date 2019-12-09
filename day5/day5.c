#include <stdio.h>
#include <stdlib.h>

#include "bootup.h"
#include "process.h"

int main(int argc, char const *argv[]) {
    int memSize;
    int* memory;

    bootup(&memory, &memSize);
    runProgram(memory, memSize);

    free(memory);
    exit(0);
}
