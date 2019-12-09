#ifndef types_h
#define types_h

#define computer struct computer
computer {
    int* memory;
    int memorySize;
    int instructionPointer;
    int output;
    int* input;
    int inputPointer;
    int running;
};

#define instruction struct instruction
instruction {
    int opCode;
    int paramAMode;
    int paramBMode;
    int paramCMode;
};

#endif
