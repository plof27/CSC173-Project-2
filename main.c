#include <stdio.h>
#include <stdlib.h>
#include "ParseTree.h"
#include "helpers/GenPrint.h"

int main() {
    printf("Hello World!\n");

    int someVar = 100;
    println(someVar);

    int *someOtherVar = &someVar;
    println(someOtherVar);

    return 0;
}
