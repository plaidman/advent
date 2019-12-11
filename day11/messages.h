#ifndef messages_h
#define messages_h

#include "types.h"

int hasMessages(Message*);
void pushMessage(Message**, int);
int popMessage(Message**);

#endif
