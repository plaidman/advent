#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bootup.h"
#include "process.h"
#include "messages.h"

int main(int argc, char const *argv[]) {
    computer* comp = bootup("input.txt");

    pushMessage(&(comp->input), 1);
    runProgram(comp);

    exit(0);
}
