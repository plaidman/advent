#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

int main(int argc, char const *argv[]) {
    Computer* comp = bootup("input.txt");

    runProgram(comp);
    int blockCount = 0;
    while (hasMessages(comp->output)) {
        popMessage(&(comp->output));
        popMessage(&(comp->output));
        Memwidth type = popMessage(&(comp->output));

        if (type == 2) {
            blockCount++;
        }
    }
    printf("%d\n", blockCount);

    comp = bootup("input.txt");
    comp->memory[0] = 2;
    Memwidth score = 0;
    Memwidth ballX = 0;
    Memwidth paddleX = 0;
    blockCount = 0;
    while (1) {
        if (ballX == paddleX) pushMessage(&(comp->input), 0);
        if (ballX > paddleX) pushMessage(&(comp->input), 1);
        if (ballX < paddleX) pushMessage(&(comp->input), -1);

        runProgram(comp);

        while (hasMessages(comp->output)) {
            Memwidth x = popMessage(&(comp->output));
            Memwidth y = popMessage(&(comp->output));
            Memwidth type = popMessage(&(comp->output));

            if (x == -1 && y == 0) {
                score = type;
            }

            if (type == 3) {
                paddleX = x;
            }

            if (type == 4) {
                ballX = x;
            }

            if (type == 2) {
                blockCount++;
            }
        }

        if (comp->haltCode == 99) {
            printf("program halted\n");
            break;
        }
    }

    exit(0);
}
