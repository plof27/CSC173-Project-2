#include "LinkedList.h"

//inserts a new element, x, to an existing list
void insertToList(LIST *pL, data_type x) {
      if ((*pL)==NULL) {
            (*pL) = (struct Node *) malloc(sizeof(struct Node));
            (*pL)->data = x;
            (*pL)->next = NULL;

      } else {
            struct Node *currentHead = (*pL);
            (*pL) = (struct Node *) malloc(sizeof(struct Node));
            (*pL)->data = x;
            (*pL)->next = currentHead;
      }
}

//deletes the item x from the list
data_type deleteFromList(LIST *pL, data_type x) {
      if ((*pL) != NULL) {
            if ((*pL)->data == x) {
                  //item found! do the things!
                  struct Node *deletedNode = (*pL);
                  data_type deletedVal = deletedNode->data;
                  (*pL) = (*pL)->next;
                  free(deletedNode);
                  return deletedVal;
            } else {
                  //try again on the next element
                  deleteFromList(&((*pL)->next), x);
            }
      } else {
            //item not found
            return NULL;
      }
}

//prints a list in order
void printList(LIST l) {
      print(l->data);
      printf(" ");
      if (l->next != NULL) {
            printList(l->next);
      } else {
            printf("\n");
      }
}

//finds whether an element is a member of the list
int lookupInList(LIST l, data_type x) {
      if (l != NULL) {
            if (l->data == x) {
                  //item found!
                  return 1;
            } else {
                  //try again on the next element
                  return lookupInList(l->next, x);
            }
      } else {
            return 0;
      }
}
