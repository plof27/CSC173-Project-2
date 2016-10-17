#ifndef LAW_RDP
#define LAW_RDP

#include "ParseTree.h"

//fcn prototypes
//for all functions, w is the string to be parsed
tree_data_type consume_input(char **w);          //returns the first character in the string and consumes it
tree_data_type look_ahead(char *w);              //returns the first character in the string (and does not consume it)
void read_strings_from_file(char *filename, int);//father function of parse_string, reads sucessive lines from a file
TREE *parse_string(char *w);                     //father function which sets things up and calls E() (eval is a flag which sets whether to evaluate the parse tree or just print it.)
TREE *E(char **w);
TREE *S(char **w);
TREE *A(char **w);
TREE *T(char **w);
TREE *P(char **w);
TREE *G(char **w);
TREE *F(char **w);
TREE *N(char **w);
TREE *B(char **w);
TREE *D(char **w);

#endif
