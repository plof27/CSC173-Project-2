#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include "GenPrint.h"

//define some stuffs
struct Node;
typedef struct Node * LIST;
typedef char data_type;
struct Node {
      data_type data;
      struct Node *next;
};

//function prototypes
void insertToList(LIST *, data_type);
data_type deleteFromList(LIST *, data_type);
void printList(LIST);
int lookupInList(LIST, data_type);
int getLength(LIST);

#endif
