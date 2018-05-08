/**
 * @file mainSuite.inc
 * 
 * Example of a simple PicoTest suite. Included by other examples to demonstrate
 * how the same suite can be integrated in a variety of situations.
 *
 * @include mainSuite.inc
 * @cond IGNORE 
 */
#include <picotest.h>

/*! [PICOTEST_SUITE examples] */
/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)
/*! [PICOTEST_SUITE examples] */

/*! [PICOTEST_CASE examples] */
#define FAILS 0
#define PASSES 1

/* Test cases */
PICOTEST_CASE(testCase1) {
    PICOTEST_VERIFY(FAILS, "assertion 1");  /* Logs error and continue */
    PICOTEST_ASSERT(FAILS, "assertion 2");  /* Logs error and abort */
    /* Unreached */
    PICOTEST_ASSERT(PASSES, "assertion 3");
}
PICOTEST_CASE(testCase2) {
    PICOTEST_ASSERT(PASSES, "assertion 1"); /* Passes */
    PICOTEST_VERIFY(FAILS, "assertion 2");  /* Logs error and continue */
}
PICOTEST_CASE(testCase3) {
    PICOTEST_ASSERT(PASSES, "assertion 1"); /* Passes */
    PICOTEST_VERIFY(FAILS, "assertion 2");  /* Passes */
}
PICOTEST_CASE(testCase4) {
    PICOTEST_VERIFY(FAILS, "assertion 1");  /* Logs error and continue */
    PICOTEST_ASSERT(FAILS, "assertion 2");  /* Logs error and abort */
}
PICOTEST_CASE(testCase5) {
    PICOTEST_ASSERT(PASSES, "assertion 1"); /* Passes */
    PICOTEST_ABORT();                       /* Stops silently. */
    /* Unreached */
    PICOTEST_VERIFY(FAILS, "assertion 2");
}
/*! [PICOTEST_CASE examples] */

/** @endcond */
