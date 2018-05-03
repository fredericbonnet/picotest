/**
 * @file matcher.c
 * 
 * Example of PicoTest test matching functions, allows custom filtering of test
 * functions.
 *
 * @include logger.c
 * @cond IGNORE 
 */
#include <stdio.h>
#include <picotest.h>

/*! [PicoTestMatchProc example] */
/* Custom test matching function declaration. */
PicoTestMatchProc matchSubstring;
#undef PICOTEST_MATCH
#define PICOTEST_MATCH matchSubstring

/* Custom test matching function. */
int matchSubstring(PicoTestProc *test, const char *testName, const char *cond) {
    /* Match tests containing **cond** substring. */
    return !!strstr(testName, cond);
}
/*! [PicoTestMatchProc example] */

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
