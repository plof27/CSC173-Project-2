#ifndef PECK_STACK
#define PECK_STACK
#include "LinkedList.h"

typedef LIST * STACK;

//fcn prototypes
STACK *createStack();       //initializes a stack and returns a pointer to it
void pushStack(STACK, int);
int popStack(STACK);
int peekStack(STACK);
void printStack(STACK);
void clearStack(STACK);    //removes everything from the stack

#endif // PECK_STACK
