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

/*! [PICOTEST_FILTER example] */
/* Custom test filter declaration. */
PicoTestFilterProc matchSubstring;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchSubstring

/* Test filter function. */
PicoTestFilterResult matchSubstring(PicoTestProc *test, const char *testName, const char *cond) {
    /* Match tests containing **cond** substring. */
    return (strstr(testName, cond) == NULL 
        ? PICOTEST_FILTER_SKIP_PROPAGATE 
        : PICOTEST_FILTER_PASS_PROPAGATE);
}
/*! [PICOTEST_FILTER example] */

/* Hooks */
PicoTestCaseEnterProc logCaseEnter;
PicoTestCaseLeaveProc logCaseLeave;
PicoTestSuiteEnterProc logSuiteEnter;
PicoTestSuiteLeaveProc logSuiteLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_CASE_ENTER logCaseEnter
#define PICOTEST_CASE_LEAVE logCaseLeave
#define PICOTEST_SUITE_ENTER logSuiteEnter
#define PICOTEST_SUITE_LEAVE logSuiteLeave

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logCaseEnter(const char *name) {
    indent(level++);
    printf("running test case %s\n", name);
}
void logCaseLeave(const char *name, int fail) {
    level--;
}
void logSuiteEnter(const char *name, int nb) {
    indent(level++);
    printf("running test suite %s\n", name);
}
void logSuiteLeave(const char *name, int nb, int fail) {
    level--;
}

/* Main test suite */
#include "mainSuite.inc"

void main() {
    /*
     * Run all tests in order:
     * 
     * running test suite mainSuite
     *   running test case testCase1
     *   running test case testCase2
     *   running test suite subSuite
     *     running test case testCase4
     *     running test case testCase5
     *   running test case testCase3
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
