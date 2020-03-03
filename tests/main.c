#include <stdio.h>

#include <picotest.h>

#include "traverse.h"

/* Main test suite */
#include "mainSuite.inc"

int main(int argc, char *argv[]) {
    int fail = 0;

    if (argc > 1 && argv[1][0] == '-') {
        if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
            /* List test cases. */
            PICOTEST_TRAVERSE(mainSuite, printTestCase);
        } else if (strcmp(argv[1], "-a") == 0 ||
                   strcmp(argv[1], "--list-all") == 0 || fail) {
            /* List all tests. */
            PICOTEST_TRAVERSE(mainSuite, printTestName);
        }
        return 0;
    }

    if (argc <= 1) {
        /* Execute all tests. */
        fail = mainSuite(NULL);
    } else {
        /* Only execute tests given as command line arguments. */
        int i;
        for (i = 1; i < argc; i++) {
            char *name = argv[i];
            fail += mainSuite(name);
        }
    }

    return fail;
}
