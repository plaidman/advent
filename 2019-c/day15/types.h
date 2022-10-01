#ifndef types_h
#define types_h

#define Memwidth long long int

#define Message struct Message
Message {
    Memwidth value;
    Message* next;
};

#define Computer struct computer
Computer {
    Memwidth* memory;
    Memwidth memorySize;
    Memwidth instructionPointer;
    Message* input;
    Message* output;
    Memwidth haltCode;
    Memwidth relBase;
};

#define Instruction struct Instruction
Instruction {
    int opCode;
    int paramAMode;
    int paramBMode;
    int paramCMode;
};

#endif
