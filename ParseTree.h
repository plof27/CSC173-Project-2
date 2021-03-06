#ifndef LAW_PARSE_TREE
#define LAW_PARSE_TREE

#include <math.h>
#include "helpers/LinkedList.h"

//alias the data type of the tree as 'tree_data_type'
//this way, if we want our tree to store something other than chars it is easy to change
//this is as close to generics as we can get
typedef char *tree_data_type;

typedef struct {
    tree_data_type data;
    int terminal;   //1 if the data stored is a terminal, 0 if the data stored is a non-terminal

    struct TNode *left;
    struct TNode *center;
    struct TNode *right;
} TNode;

typedef TNode * TREE;

//fcn prototypes
TREE * create_tree(tree_data_type);                     //creates a tree with root element tree_data_type and returns a pointer to that tree
int insert_to_leftmost_nonterminal(TREE, LIST);         //adds the data in the list to the tree at the leftmost non-terminal element
tree_data_type evaluate_tree(TREE);                     //evaluates the tree and frees all nodes from memory
void evaluate_tree_helper(TREE);                        //the thing that does the legwork of evaluate_tree
tree_data_type *evaluate_node(tree_data_type, tree_data_type, tree_data_type);                     //takes a node with three terminal children and returns the evaluation of those children
void free_tree(TREE);                                   //frees all the trees nodes from memory
void print_tree(TREE);                                  //prints the tree all nicely
void print_tree_helper(TREE, char*, int);               //helper function to print_tree, this is what actually does the recursion
int count_tree_nodes(TREE);                             //counts the number of nodes in the tree

#endif
