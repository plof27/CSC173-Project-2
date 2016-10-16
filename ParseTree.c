#include <stdlib.h>
#include <stdio.h>
#include "ParseTree.h"

TREE * create_tree(tree_data_type x) {
    TREE *pT = (TREE *) malloc(sizeof(TREE));
    (*pT)->data = x;
    (*pT)->terminal = 0;    //the first element should always be a non-terminal (make this better later~)

    (*pT)->left = NULL;
    (*pT)->center = NULL;
    (*pT)->right = NULL;

    return pT;
}

int insert_to_leftmost_nonterminal(TREE t, LIST l) {
    //stuff~
}

int evaluate_tree(TREE t) {
    //stuff~
}

void free_tree(TREE t) {
    //stuff~
}

void print_tree(TREE t) {
    //create a string buffer to store the final tree string
    char buf[100];      //fix later to make more general~

    //create a string which contains only the root data
    char str[2];
    str[0] = t->data;
    str[1] = '\0';

    //copy that string into the buffer and append a newline and a tab
    strcpy(buf, str);
    strcat(buf, "(\n\t");

    //do the recursive stuff to build the middle of the string (all non-root nodes)
    print_tree_helper(t, buf, 1);

    //finish off the string and print it
    strcat(buf, ")");
    printf("%s\n", buf);
}

void print_tree_helper(TREE t, char *buf, int level) {
    int i;
    if (t->left != NULL) {
        //Im not gonna comment the next two blocks; assume without loss of generality
        strcat(buf, "(");

        //create the a string from the left child's data and append it
        char str[2];
        TREE tmp = t->left;     //need to do this because gcc is a silly, silly compiler and doing it inline caused undefined behavior
        str[0] = tmp->data;
        str[1] = '\0';
        strcat(buf, str);

        //recurse for children
        print_tree_helper(t->left, buf, level+1);

        //append newline and the appropriate number of tabs
        strcat(buf, ")\n");
        for (i=0; i<level; i++) strcat(buf, "\t");
    }
    if (t->center != NULL) {
        strcat(buf, "(");
        char str[2];
        TREE tmp = t->center;
        str[0] = tmp->data;
        str[1] = '\0';
        strcat(buf, str);
        print_tree_helper(t->center, buf, level+1);
        strcat(buf, ")\n");
        for (i=0; i<level; i++) strcat(buf, "\t");
    }
    if (t->right != NULL) {
        strcat(buf, "(");
        char str[2];
        TREE tmp = t->right;
        str[0] = tmp->data;
        str[1] = '\0';
        strcat(buf, str);
        print_tree_helper(t->right, buf, level+1);
        strcat(buf, ")\n");
        for (i=0; i<level; i++) strcat(buf, "\t");
    }

}
