#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void pushMessage(Message** messageStack, int value) {
    // printf("pushing %d\n", value);
    Message* new = malloc(sizeof(Message));
    new->value = value;
    new->next = NULL;

    if (*messageStack == NULL) {
        *messageStack = new; 
        return;
    }

    Message* current = *messageStack;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new;
}

int hasMessages(Message* messageStack) {
    if (messageStack == NULL) {
        return 0;
    }

    return 1;
}

int popMessage(Message** messageStack) {
    if (*messageStack == NULL) {
        printf("buffer overflow\n");
        exit(1);
    }

    int value = (*messageStack)->value;
    *messageStack = (*messageStack)->next;
    // printf("popping %d\n", value);

    return value;
}
