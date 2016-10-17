#include <stdlib.h>
#include <stdio.h>
#include "ParseTree.h"

TREE *create_tree(tree_data_type x) {
    LIST terminals = NULL;
    insertToList(&terminals, "+");
    insertToList(&terminals, "-");
    insertToList(&terminals, "*");
    insertToList(&terminals, "/");
    insertToList(&terminals, "(");
    insertToList(&terminals, ")");
    insertToList(&terminals, "0");
    insertToList(&terminals, "1");
    insertToList(&terminals, "2");
    insertToList(&terminals, "3");
    insertToList(&terminals, "4");
    insertToList(&terminals, "5");
    insertToList(&terminals, "6");
    insertToList(&terminals, "7");
    insertToList(&terminals, "8");
    insertToList(&terminals, "9");

    TREE t = (TREE) malloc(sizeof(TNode));
    t->terminal = lookupInList(terminals, x);
    t->data = x;

    t->left = NULL;
    t->center = NULL;
    t->right = NULL;

    deleteFromList(&terminals, "+");
    deleteFromList(&terminals, "-");
    deleteFromList(&terminals, "*");
    deleteFromList(&terminals, "/");
    deleteFromList(&terminals, "(");
    deleteFromList(&terminals, ")");
    deleteFromList(&terminals, "e");
    deleteFromList(&terminals, "0");
    deleteFromList(&terminals, "1");
    deleteFromList(&terminals, "2");
    deleteFromList(&terminals, "3");
    deleteFromList(&terminals, "4");
    deleteFromList(&terminals, "5");
    deleteFromList(&terminals, "6");
    deleteFromList(&terminals, "7");
    deleteFromList(&terminals, "8");
    deleteFromList(&terminals, "9");

    return &t;
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
            insert_to_leftmost_nonterminal(t->right, l);
        }
        return 0;
    }
}

tree_data_type evaluate_tree(TREE t) {
}

tree_data_type evaluate_node(tree_data_type left, tree_data_type center, tree_data_type right) {

    if (strcmp(left, "(") == 0) {
        //trivial case, will only be called on (x)
        return center;
    } else if (strcmp(center, "+") == 0) {
        //read the operands to floats
        float l = atof(left);
        float r = atof(right);
        //do the operation
        l += r;
        //create a string buffer large enough for the result
        char buf[floor(log10(l)+1)+7];
        //print the result to the buffer
        sprintf(buf, "%.6f", l);
        return buf;
    } else if (strcmp(center, "-") == 0) {
        float l = atof(left);
        float r = atof(right);
        l -= r;
        char buf[floor(log10(l)+1)+7];
        sprintf(buf, "%.6f", l);
        return buf;
    char buf[floor(log10(l)+1)+7];
    } else if (strcmp(center, "*") == 0) {
        float l = atof(left);
        float r = atof(right);
        l *= r;
        char buf[floor(log10(l)+1)+7];
        sprintf(buf, "%.6f", l);
        return buf;
    } else if (strcmp(center, "/") == 0) {
        float l = atof(left);
        float r = atof(right);
        l /= r;
        char buf[floor(log10(l)+1)+7];
        sprintf(buf, "%.6f", l);
        return buf;
    }
}

void free_tree(TREE t) {
    if (t->left != NULL) {
        free_tree(t->left);
    }
    if (t->center != NULL) {
        free_tree(t->center);
    }
    if (t->right != NULL) {
        free_tree(t->right);
    }
    free(t);
}

void print_tree(TREE t) {
    //create a string buffer to store the final tree string
    char buf[100];      //fix later to make more general~

    //copy that string into the buffer and append a newline and a tab
    strcpy(buf, t->data);
    strcat(buf, "(");
    if (t->left != NULL) strcat(buf, "\n");

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

        //append an appropriate number of tabs and the (
        for (i=0; i<level; i++) strcat(buf, "\t");
        strcat(buf, "(");

        TREE tmp = t->left;     //need to do this because gcc is a silly, silly compiler and doing it inline caused undefined behavior
        strcat(buf, tmp->data);
        if (tmp->left != NULL) strcat(buf, "\n");

        //recurse for children
        print_tree_helper(t->left, buf, level+1);

        //append ) and the newline if appropriate
        strcat(buf, ")");
        if (t->center != NULL || t->right != NULL) {
            strcat(buf, "\n");
        }
    }
    if (t->center != NULL) {
        for (i=0; i<level; i++) strcat(buf, "\t");
        strcat(buf, "(");
        TREE tmp = t->center;
        strcat(buf, tmp->data);
        if (tmp->left != NULL) strcat(buf, "\n");
        print_tree_helper(t->center, buf, level+1);
        strcat(buf, ")");
        if (t->right != NULL) {
            strcat(buf, "\n");
        }
    }
    if (t->right != NULL) {
        for (i=0; i<level; i++) strcat(buf, "\t");
        strcat(buf, "(");
        TREE tmp = t->right;
        strcat(buf, tmp->data);
        if (tmp->left != NULL) strcat(buf, "\n");
        print_tree_helper(t->right, buf, level+1);
        strcat(buf, ")");
    }

}
