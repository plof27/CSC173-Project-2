#include <stdlib.h>
#include "Stack.h"

STACK *createStack() {
    STACK newStack = malloc(sizeof(LIST));
    *(newStack) = NULL;
    return &newStack;
}

void pushStack(STACK s, int x) {
    insertToList(s, x);
}

int popStack(STACK s) {
    if ((*s) != NULL) {
        int retval = (*s)->data;
        deleteFromList(s, retval);
        return retval;
    } else {
        printf("Cannot pop, stack nonexistant.\n");
        return 0;
    }
}

int peekStack(STACK s) {
    if ((*s) != NULL) return (*s)->data;
    else return 0;
}

void printStack(STACK s) {
    if ((*s) != NULL) printList(*s);
    else printf("The stack is empty.\n");
}

void clearStack(STACK s) {
    if ((*s) != NULL) {
        //stack still has elements!
        struct Node *deletedNode = *s;
        (*s) = (*s)->next;
        free(deletedNode);
        clearStack(s);
    }
}
