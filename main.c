#include <stdio.h>
#include <stdlib.h>
#include "ParseTree.h"
#include "helpers/GenPrint.h"

int main() {

    /* GenPrint demo code
    int someVar = 100;
    println(someVar);

    int *someOtherVar = &someVar;
    println(someOtherVar);
    */

    char str[20];
    float f = 4.446;
    sprintf(str, "%.6f", f);
    printf("%s\n", str);

    TREE parse_tree_test = *(create_tree("A"));

    LIST to_be_added = NULL;
    insertToList(&to_be_added, "D");
    insertToList(&to_be_added, "C");
    insertToList(&to_be_added, "1");

    insert_to_leftmost_nonterminal(parse_tree_test, to_be_added);

    deleteFromList(&to_be_added, "1");
    deleteFromList(&to_be_added, "C");
    deleteFromList(&to_be_added, "D");
    insertToList(&to_be_added, "3");
    insertToList(&to_be_added, "2");

    insert_to_leftmost_nonterminal(parse_tree_test, to_be_added);

    deleteFromList(&to_be_added, "2");
    deleteFromList(&to_be_added, "3");
    insertToList(&to_be_added, "G");

    insert_to_leftmost_nonterminal(parse_tree_test, to_be_added);

    deleteFromList(&to_be_added, "G");
    insertToList(&to_be_added, "H");

    insert_to_leftmost_nonterminal(parse_tree_test, to_be_added);

    print_tree(parse_tree_test);

    return 0;
}