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
    char *str = "";

}

void print_tree_helper(TREE t, char *str) {

}
