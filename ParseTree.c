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

/*THIS FUNCTION IS BAD DON'T USE IT
tree_data_type evaluate_tree(TREE t) {
    TREE left = t->left;
    TREE center = t->center;
    TREE right = t->right;

    //find the number of terminal and non-terminal children
    int num_terminal_children = 0;
    int num_non_terminal_children = 0;

    if (left != NULL) {
        if (left->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }
    if (center != NULL) {
        if (center->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }
    if (right != NULL) {
        if (right->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }

    //NOW FOR THE FUN PART
    if (num_non_terminal_children == 0) {
        //base case: all children are terminals
        if (num_terminal_children == 0) {
            //leaf found (which shouldn't happen)
            return "Unable to evaluate node with no children\n";
        } else if (num_terminal_children == 1) {
            //only child is 1 terminal, so bubble it up (will always be the left child because children are inserted left first)
            t->data = left->data;
            t->terminal = 1;
            free(left);
            t->left == NULL;
        } else if (num_terminal_children == 2) {
            //this is either the +x case (which is handled below), or it is the concatenation of a number and a digit
            if (strcmp(t->data, "N") == 0) {
                t->data = strcat(left->data, center->data);
                t->terminal = 1;
                free(left);
                free(center);
                t->left = NULL;
                t->center = NULL;
            }
        } else {
            //three terminal children, this means we have an expression to evaluate
            t->data = evaluate_node(left->data, center->data, right->data);
            t->terminal = 1;
            free(left);
            free(center);
            free(right);
            t->left = NULL;
            t->center = NULL;
            t->right = NULL;
        }
    } else {
        //some of the children are non terminals. This must be fixed.
        //first, recurse down on each non-terminal child
        if (left->terminal == 0) evaluate_tree(left);
        if (center->terminal == 0) evaluate_tree(center);
        if (right->terminal == 0) evaluate_tree(right);

        //remove any children which contain the empty string
        if (strcmp(left->data, "e") == 0) {
            free(left);
            t->left = NULL;
        }
        if (strcmp(center->data, "e") == 0) {
            free(center);
            t->center = NULL;
        }
        if (strcmp(right->data, "e") == 0) {
            free(right);
            t->right = NULL;
        }

        //update the number of terminal and non-terminal children
        num_terminal_children = 0;
        num_non_terminal_children = 0;

        if (left != NULL) {
            if (left->terminal == 1) {
                num_terminal_children++;
            } else {
                num_non_terminal_children++;
            }
        }
        if (center != NULL) {
            if (center->terminal == 1) {
                num_terminal_children++;
            } else {
                num_non_terminal_children++;
            }
        }
        if (right != NULL) {
            if (right->terminal == 1) {
                num_terminal_children++;
            } else {
                num_non_terminal_children++;
            }
        }

        if (num_non_terminal_children > 0) {
            //non terminal children exists only in the +x case
            if (num_non_terminal_children == 1) {
                //only 1 non terminal child, copy the information in its children to t's children
                if (left != NULL) {
                    TREE tmp1 = left->left;
                    TREE tmp2 = left->center;
                    t->center = *(create_tree(tmp2->data));
                    left->data = tmp1->data;

                    left->terminal = 1;
                    center->terminal = 1;

                    free(tmp1);
                    free(tmp2);
                } else if (center != NULL) {
                    TREE tmp1 = center->left;
                    TREE tmp2 = center->center;
                    t->left = *(create_tree(tmp1->data));
                    center->data = tmp2->data;

                    left->terminal = 1;
                    center->terminal = 1;

                    free(tmp1);
                    free(tmp2);
                } else {
                    TREE tmp1 = right->left;
                    TREE tmp2 = right->center;
                    t->left = *(create_tree(tmp1->data));
                    t->center = *(create_tree(tmp2->data));

                    left->terminal = 1;
                    center->terminal = 1;

                    free(tmp1);
                    free(tmp2);
                    free(right);
                    t->right = NULL;
                }
            } else if (num_non_terminal_children == 2) {
                //original experssion was of the form x+y+z, resulting in a +x+y tree structure
                TREE leftleft = left->left;
                TREE leftcenter = left->center;
                TREE centerleft = center->left;
                TREE centercenter = center->center;

                center->data = evaluate_node(leftcenter->data, centerleft->data, centercenter->data);
                left->data = leftleft->data;

                left->terminal = 1;
                center->terminal = 1;

                free(leftleft);
                free(leftcenter);
                free(centerleft);
                free(centercenter);
            } else {
                //1 terminal child and 1 non-terminal child
                TREE centerleft = center->left;
                TREE centercenter = center->center;

                t->data = evaluate_node(left->data, centerleft->data, centercenter->data);
                t->terminal = 1;

                free(centerleft);
                free(centercenter);
                free(left);
                free(center);
            }
        } else {
            //all children are terminals (recursion "succeeded")
            if (num_terminal_children == 0) {
                //leaf found (which shouldn't happen)
                return "Unable to evaluate node with no children\n";
            } else if (num_terminal_children == 1) {
                //only child is 1 terminal, so bubble it up (will always be the left child because children are inserted left first)
                t->data = left->data;
                t->terminal = 1;
                free(left);
                t->left == NULL;
            } else if (num_terminal_children == 2) {
                //this is either the +x case (which is handled below), or it is the concatenation of a number and a digit
                if (strcmp(t->data, "N") == 0) {
                    t->data = strcat(left->data, center->data);
                    t->terminal = 1;
                    free(left);
                    free(center);
                    t->left = NULL;
                    t->center = NULL;
                }
            } else {
                //three terminal children, this means we have an expression to evaluate
                t->data = evaluate_node(left->data, center->data, right->data);
                t->terminal = 1;
                free(left);
                free(center);
                free(right);
                t->left = NULL;
                t->center = NULL;
                t->right = NULL;
            }
        }

    }

}
*/

tree_data_type evaluate_tree(TREE t) {
    TREE left = t->left;
    TREE center = t->center;
    TREE right = t->right;

    //some of the children may be non terminals. This must be fixed.
    //first, recurse down on each non-terminal child
    if (left->terminal == 0) evaluate_tree(left);
    if (center->terminal == 0) evaluate_tree(center);
    if (right->terminal == 0) evaluate_tree(right);

    //remove any children which contain the empty string (not relevant for evaluation)
    if (strcmp(left->data, "e") == 0) {
        free(left);
        t->left = NULL;
    }
    if (strcmp(center->data, "e") == 0) {
        free(center);
        t->center = NULL;
    }
    if (strcmp(right->data, "e") == 0) {
        free(right);
        t->right = NULL;
    }

    //set the number of terminal and non-terminal children
    int num_terminal_children = 0;
    int num_non_terminal_children = 0;

    if (left != NULL) {
        if (left->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }
    if (center != NULL) {
        if (center->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }
    if (right != NULL) {
        if (right->terminal == 1) {
            num_terminal_children++;
        } else {
            num_non_terminal_children++;
        }
    }

    if (num_non_terminal_children > 0) {
        //non terminal children exists only in the +x case
        if (num_non_terminal_children == 1) {
            //only 1 non terminal child, copy the information in its children to t's children
            if (left != NULL) {
                TREE tmp1 = left->left;
                TREE tmp2 = left->center;
                t->center = *(create_tree(tmp2->data));
                left->data = tmp1->data;

                left->terminal = 1;
                center->terminal = 1;

                free(tmp1);
                free(tmp2);
            } else if (center != NULL) {
                TREE tmp1 = center->left;
                TREE tmp2 = center->center;
                t->left = *(create_tree(tmp1->data));
                center->data = tmp2->data;

                left->terminal = 1;
                center->terminal = 1;

                free(tmp1);
                free(tmp2);
            } else {
                TREE tmp1 = right->left;
                TREE tmp2 = right->center;
                t->left = *(create_tree(tmp1->data));
                t->center = *(create_tree(tmp2->data));

                left->terminal = 1;
                center->terminal = 1;

                free(tmp1);
                free(tmp2);
                free(right);
                t->right = NULL;
            }
        } else if (num_non_terminal_children == 2) {
            //original experssion was of the form x+y+z, resulting in a +x+y tree structure (+x has "caught up" to +y)
            TREE leftleft = left->left;
            TREE leftcenter = left->center;
            TREE centerleft = center->left;
            TREE centercenter = center->center;

            center->data = evaluate_node(leftcenter->data, centerleft->data, centercenter->data);
            left->data = leftleft->data;

            left->terminal = 1;
            center->terminal = 1;

            free(leftleft);
            free(leftcenter);
            free(centerleft);
            free(centercenter);
        } else {
            //1 terminal child and 1 non-terminal child (the left operand has "caught up" to the operator and right operand)
            TREE centerleft = center->left;
            TREE centercenter = center->center;

            t->data = evaluate_node(left->data, centerleft->data, centercenter->data);
            t->terminal = 1;

            free(centerleft);
            free(centercenter);
            free(left);
            free(center);
        }
    } else {
        //all children are terminals (recursion "succeeded")
        if (num_terminal_children == 0) {
            //leaf found (which shouldn't happen)
            return "Unable to evaluate node with no children\n";
        } else if (num_terminal_children == 1) {
            //only child is 1 terminal, so bubble it up (will always be the left child because children are inserted left first)
            t->data = left->data;
            t->terminal = 1;
            free(left);
            t->left == NULL;
        } else if (num_terminal_children == 2) {
            //this is either the +x case (which is handled above), or it is the concatenation of a number and a digit
            if (strcmp(t->data, "N") == 0) {
                t->data = strcat(left->data, center->data);
                t->terminal = 1;
                free(left);
                free(center);
                t->left = NULL;
                t->center = NULL;
            }
        } else {
            //three terminal children, this means we have an expression to evaluate
            t->data = evaluate_node(left->data, center->data, right->data);
            t->terminal = 1;
            free(left);
            free(center);
            free(right);
            t->left = NULL;
            t->center = NULL;
            t->right = NULL;
        }
    }

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
        char buf[(int) (floor(log10(l)+1)+7)];
        //print the result to the buffer
        sprintf(buf, "%.6f", l);
        return buf;
    } else if (strcmp(center, "-") == 0) {
        float l = atof(left);
        float r = atof(right);
        l -= r;
        char buf[(int) (floor(log10(l)+1)+7)];
        sprintf(buf, "%.6f", l);
        return buf;
    } else if (strcmp(center, "*") == 0) {
        float l = atof(left);
        float r = atof(right);
        l *= r;
        char buf[(int) (floor(log10(l)+1)+7)];
        sprintf(buf, "%.6f", l);
        return buf;
    } else if (strcmp(center, "/") == 0) {
        float l = atof(left);
        float r = atof(right);
        l /= r;
        char buf[(int) (floor(log10(l)+1)+7)];
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
    int n = count_tree_nodes(t);
    char buf[(n*n)+(4*n)+1];

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

int count_tree_nodes(TREE t) {
    if (t->left == NULL && t->center == NULL && t->right == NULL) {
        return 1;
    } else {
        int retval = 1;
        if (t->left != NULL) {
            retval += count_tree_nodes(t->left);
        }
        if (t->center != NULL) {
            retval += count_tree_nodes(t->center);
        }
        if (t->right != NULL) {
            retval += count_tree_nodes(t->right);
        }
        return retval;
    }
}
