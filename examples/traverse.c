/**
 * @file traverse.c
 *
 * Example of PicoTest hierarchy traversal, prints traversed tests to stdout.
 * 
 * @include traverse.c
 * @cond IGNORE 
 */
#include <stdio.h>
#include <picotest.h>


/*! [PicoTestTraverseProc example] */
/* Forward declaration. */
PicoTestTraverseProc printTestCase;
PicoTestTraverseProc printTestName;

/* Traversal proc, will print test cases only. */
void printTestCase(const char *name, int nb) {
    if (nb == 0) printf("%s\n", name);
}

/* Traversal proc, will print all tests. */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}
/*! [PicoTestTraverseProc example] */

/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)

/* Test cases */
PICOTEST_CASE(testCase1) { /* ... */ }
PICOTEST_CASE(testCase2) { /* ... */ }
PICOTEST_CASE(testCase3) { /* ... */ }
PICOTEST_CASE(testCase4) { /* ... */ }
PICOTEST_CASE(testCase5) { /* ... */ }

void main() {
    /* 
     * Traverse and print all test cases in order:
     * 
     * testCase1
     * testCase2
     * testCase4
     * testCase5
     * testCase3
     */
    printf("Print all test cases:\n");
    PICOTEST_TRAVERSE(mainSuite, printTestCase);
    printf("\n");

    /* 
     * Traverse and print all tests in order, including suites:
     * 
     * mainSuite
     * testCase1
     * testCase2
     * subSuite
     * testCase4
     * testCase5
     * testCase3
     */
    printf("Print all tests:\n");
    PICOTEST_TRAVERSE(mainSuite, printTestName);
    printf("\n");

    /* 
     * Traverse and print a sub-suite:
     * 
     * subSuite
     * testCase4
     * testCase5
     */
    printf("Print all tests under subSuite:\n");
    PICOTEST_TRAVERSE(subSuite, printTestName);
    printf("\n");

    /* 
     * Traverse individual test cases:
     * 
     * testCase2
     */
    printf("Print individual test cases:\n");
    PICOTEST_TRAVERSE(testCase2, printTestName);
    PICOTEST_TRAVERSE(testCase5, printTestName);
    printf("\n");
}
/** @endcond */
