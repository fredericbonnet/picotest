<a id="traverse_8c"></a>
# File traverse.c

![][C++]

**Location**: `examples/traverse.c`

Example of PicoTest hierarchy traversal, prints traversed tests to stdout.

```cpp

#include <stdio.h>
#include <picotest.h>

/* Test traversal function declaration. */
PicoTestTraverseProc printTestCase;
PicoTestTraverseProc printTestName;

/* Traversal function, will print test cases only. */
void printTestCase(const char *name, int nb) {
    if (nb == 0) printf("%s\n", name);
}

/* Traversal function, will print all tests. */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}

/* Main test suite */
#include "mainSuite.inc"

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
```

## Source


```cpp

#include <stdio.h>
#include <picotest.h>

/* Test traversal function declaration. */
PicoTestTraverseProc printTestCase;
PicoTestTraverseProc printTestName;

/* Traversal function, will print test cases only. */
void printTestCase(const char *name, int nb) {
    if (nb == 0) printf("%s\n", name);
}

/* Traversal function, will print all tests. */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}

/* Main test suite */
#include "mainSuite.inc"

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
```


[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)