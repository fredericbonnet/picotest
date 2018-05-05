/**
 * @file filter.c
 * 
 * Example of PicoTest test filter, allows custom filtering of test functions.
 *
 * @include filter.c
 * @cond IGNORE 
 */
#include <stdio.h>
#include <picotest.h>

/*! [PicoTestFilterProc example] */
/* Custom test filter declaration. */
PicoTestFilterProc matchSubstring;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchSubstring

/* Custom test filter function. */
PicoTestFilterResult matchSubstring(PicoTestProc *test, const char *testName, const char *cond) {
    /* Match tests containing **cond** substring. */
    return (strstr(testName, cond) == NULL 
        ? PICOTEST_FILTER_SKIP_PROPAGATE 
        : PICOTEST_FILTER_PASS_PROPAGATE);
}
/*! [PicoTestFilterProc example] */

/* Hooks */
PicoTestCaseEnterProc logCase;
PicoTestSuiteEnterProc logSuite;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER logCase
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER logSuite

void logCase(const char *name) {
    printf("running test case %s\n", name);
}
void logSuite(const char *name, int nb) {
    printf("running test suite %s\n", name);
}

/* Main test suite */
#include "mainSuite.inc"

void main() {
    /*
     * Run all tests in order:
     * 
     * running test suite mainSuite
     * running test case testCase1
     * running test case testCase2
     * running test suite subSuite
     * running test case testCase4
     * running test case testCase5
     * running test case testCase3
     */
    printf("Run all tests:\n");
    mainSuite(NULL);
    printf("\n");

    /*
     * Run tests containing the string "Case":
     * 
     * running test case testCase1
     * running test case testCase2
     * running test case testCase4
     * running test case testCase5
     * running test case testCase3
     */
    printf("Run tests containing \"Case\":\n");
    mainSuite("Case");
    printf("\n");
}
/** @endcond */
