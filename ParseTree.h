#ifndef LAW_PARSE_TREE
#define LAW_PARSE_TREE

//alias the data type of the tree as 'datatype'
//this way, if we want our tree to store something other than chars it is easy to change
//this is as close to generics as we can get
typedef char datatype;

typedef struct {
    datatype data;

    struct TNode *left;
    struct TNode *center;
    struct TNode *right;
} TNode;

//fcn prototypes


#endif
