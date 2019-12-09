#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

void stringify(int, char*);
int validate(char*);
void split(char*, int*);
void shift(char*);

int main(int argc, char const *argv[]) {
    computer* source = bootup("input.txt");
    computer* comps[5];

    for (int i = 0; i < 5; i++) {
        comps[i] = bootup("input.txt");
    }

    int largest = 0;
    char phaseString[6];
    int phases[5];
    for (int i = 1232; i < 43212; i++) {
        for (int i = 0; i < 5; i++) {
            memcpy(comps[i]->memory, source->memory, sizeof(int) * source->memorySize);
            comps[i]->instructionPointer = 0;
        }

        stringify(i, phaseString);
        if (validate(phaseString) == 0) {
            continue;
        }
        split(phaseString, phases);

        printf("phases %s\n", phaseString);

        int signal = 0;
        for (int j = 0; j < 5; j++) {
            pushMessage(&(comps[j]->input), phases[j]);
            pushMessage(&(comps[j]->input), signal);

            runProgram(comps[j]);
            signal = popMessage(&(comps[j]->output));
        }

        if (signal > largest) {
            largest = signal;
        }

        printf("output for %s: %d\n", phaseString, signal);
    }

    printf("largest: %d\n", largest);
    exit(0);
}

void stringify(int phases, char* phaseString) {
    sprintf(phaseString, "%d", phases);

    if (phases < 10000) {
        shift(phaseString);
    }
}

void shift(char* phases) {
    phases[5] = '\0';
    phases[4] = phases[3];
    phases[3] = phases[2];
    phases[2] = phases[1];
    phases[1] = phases[0];
    phases[0] = '0';
}

int validate(char* phases) {
    if (strlen(phases) != 5) {
        return 0;
    }

    char correctPhases[] = "01234";
    for (int i = 0; i < strlen(correctPhases); i++) {
        if (strchr(phases, correctPhases[i]) == NULL) {
            return 0;
        }
    }

    return 1;
}

void split(char* phaseString, int* phases) {
    for (int i = 0; i < 5; i++) {
        phases[i] = phaseString[i] - '0';
    }
}
