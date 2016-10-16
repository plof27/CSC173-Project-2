#include <stdlib.h>
#include <stdio.h>
#include "ParseTree.h"

TREE * create_tree(tree_data_type x) {
    LIST terminals = NULL;
    insertToList(&terminals, '+');
    insertToList(&terminals, '-');
    insertToList(&terminals, '*');
    insertToList(&terminals, '/');
    insertToList(&terminals, '(');
    insertToList(&terminals, ')');
    int i;
    for (i=48; i<58; i++) {
        char c = (char) i;
        insertToList(&terminals, c);
    }

    TREE *pT = (TREE *) malloc(sizeof(TREE));
    (*pT)->data = x;
    (*pT)->terminal = lookupInList(terminals, x);

    (*pT)->left = NULL;
    (*pT)->center = NULL;
    (*pT)->right = NULL;

    deleteFromList(&terminals, '+');
    deleteFromList(&terminals, '-');
    deleteFromList(&terminals, '*');
    deleteFromList(&terminals, '/');
    deleteFromList(&terminals, '(');
    deleteFromList(&terminals, ')');
    for (i=48; i<58; i++) {
        char c = (char) i;
        deleteFromList(&terminals, c);
    }

    return pT;
}

int insert_to_leftmost_nonterminal(TREE t, LIST l) {
    if (t->terminal == 0 && t->left == NULL) {
        //leftmost non-terminal found!
        int list_length = getLength(l); //find how many things are being added
        if (list_length == 1) {
            //insert to left only
            TREE new_node = *(create_tree(l->data));

            t->left = new_node;
        } else if (list_length == 2) {
            //insert to left and center
            TREE new_left_node = *(create_tree(l->data));
            l = l->next;
            TREE new_center_node = *(create_tree(l->data));

            t->left = new_left_node;
            t->center = new_center_node;
        } else if (list_length == 3) {
            //insert to all three
            TREE new_left_node = *(create_tree(l->data));
            l = l->next;
            TREE new_center_node = *(create_tree(l->data));
            l= l->next;
            TREE new_right_node = *(create_tree(l->data));

            t->left = new_left_node;
            t->center = new_center_node;
            t->right = new_right_node;
        } else {
                printf("%s\n", "Error inserting elements");
        }

        return 1;
    } else {
        int flag = 0;
        if (t->left != NULL) {
            flag = insert_to_leftmost_nonterminal(t->left, l);
        }
        if (t->center != NULL && flag == 0) {
            flag = insert_to_leftmost_nonterminal(t->center, l);
        }
        if (t->right != NULL && flag == 0) {
            insert_to_leftmost_nonterminal(t-> center, l);
        }
        return 0;
    }
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
        if (t->center !=NULL || t->right !=NULL) for (i=0; i<level; i++) strcat(buf, "\t");
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
        if (t->right !=NULL) for (i=0; i<level; i++) strcat(buf, "\t");
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
    }

}
