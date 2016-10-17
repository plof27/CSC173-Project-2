#include <stdio.h>
#include <stdlib.h>
#include "ParseTree.h"
#include "RDP.h"
#include "helpers/GenPrint.h"

int main() {

    /* GenPrint demo code
    int someVar = 100;
    println(someVar);

    int *someOtherVar = &someVar;
    println(someOtherVar);
    */

    /*ParseTree testing code
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
    */

    read_strings_from_file("somefile.txt", 0);

    return 0;
}
