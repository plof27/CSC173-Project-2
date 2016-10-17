#include <stdlib.h>
#include <stdio.h>
#include "RDP.h"

tree_data_type consume_input(char **w) {
    char str[2];
    strcpy(str, w[0]);
    strcat(str, "\0");
    w++;
    return str;
}

tree_data_type look_ahead(char *w) {
    char str[2];
    strcpy(str, w[0]);
    strcat(str, "\0");
    return str;
}

void read_strings_from_file(char *filename) {
    //stuff~
}

TREE parse_string(char *w) {
    //stuff~
}

TREE E(char *w) {
    //stuff~
}

TREE S(char *w) {
    //stuff~
}

TREE A(char *w) {
    //stuff~
}

TREE T(char *w) {
    //stuff~
}

TREE P(char *w) {
    //stuff~
}

TREE G(char *w) {
    //stuff~
}

TREE F(char *w) {
    //stuff~
}

TREE N(char *w) {
    //stuff~
}

TREE B(char *w) {
    //stuff~
}

TREE D(char *w) {
    //stuff~
}
