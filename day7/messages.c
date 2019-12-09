#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void pushMessage(message** messageStack, int value) {
    message* new = malloc(sizeof(message));
    new->value = value;
    new->next = NULL;

    if (*messageStack == NULL) {
        *messageStack = new; 
        return;
    }

    message* current = *messageStack;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new;
}

int hasMessages(message* messageStack) {
    if (messageStack == NULL) {
        return 0;
    }

    return 1;
}

int popMessage(message** messageStack) {
    if (*messageStack == NULL) {
        printf("buffer overflow\n");
        exit(1);
    }

    int value = (*messageStack)->value;
    *messageStack = (*messageStack)->next;

    return value;
}
