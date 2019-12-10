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
    message* input;
    message* output;
    int haltCode;
    int relBase;
};

#define instruction struct instruction
instruction {
    int opCode;
    int paramAMode;
    int paramBMode;
    int paramCMode;
};

#endif
