#ifndef types_h
#define types_h

#define message struct message
message {
    int value;
    message* next;
};

#define computer struct computer
computer {
    int* memory;
    int memorySize;
    int instructionPointer;
    int* input;
    message* output;
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
