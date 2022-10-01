#ifndef messages_h
#define messages_h

#include "types.h"

int hasMessages(message*);
void pushMessage(message**, int);
int popMessage(message**);

#endif
