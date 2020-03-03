#include <stdio.h>

#include <picotest.h>

#include "traverse.h"

/* Traversal function, will print test cases only */
void printTestCase(const char *name, int nb) {
    if (nb == 0)
        printf("%s\n", name);
}

/* Traversal function, will print all tests */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}
