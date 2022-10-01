#ifndef types_h
#define types_h

#define memwidth long long int

#define message struct message
message {
    memwidth value;
    message* next;
};

#define computer struct computer
computer {
    memwidth* memory;
    memwidth memorySize;
    memwidth instructionPointer;
    message* input;
    message* output;
    memwidth haltCode;
    memwidth relBase;
};

#define instruction struct instruction
instruction {
    int opCode;
    int paramAMode;
    int paramBMode;
    int paramCMode;
};

#endif
