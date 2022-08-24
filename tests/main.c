#include <stdio.h>

#include <picotest.h>

#include "hooks.h"
#include "traverse.h"

/* Main test suite */
#include "mainSuite.inc"

int main(int argc, char *argv[]) {
    int json = 0;
    int fail = 0;

    if (argc > 1 && argv[1][0] == '-') {
        if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
            /* List test cases. */
            PICOTEST_TRAVERSE(mainSuite, printTestCase);
            return 0;
        } else if (strcmp(argv[1], "-a") == 0 ||
                   strcmp(argv[1], "--list-all") == 0) {
            /* List all tests. */
            PICOTEST_TRAVERSE(mainSuite, printTestName);
            return 0;
        } else if (strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--hierarchy") == 0) {
            /* List all tests. */
            PICOTEST_VISIT(mainSuite, printTestHierarchy);
            return 0;
        } else if (strcmp(argv[1], "-J") == 0 ||
                   strcmp(argv[1], "--list-json") == 0) {
            /* Print test suite as JSON. */
            PICOTEST_VISIT(mainSuite, printTestSuiteJson);
            return 0;
        }

        if (strcmp(argv[1], "-j") == 0 || strcmp(argv[1], "--json") == 0) {
            /* Use JSON hooks. */
            json = 1;
            argc--;
            argv++;
        }
    }

    initHooks(json);

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
