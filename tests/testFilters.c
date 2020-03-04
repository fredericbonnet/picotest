#include <picotest.h>

/*
 * Test utilities
 */

/* Filters and hooks used for testing */
static int filterCalled, testCaseCalled;
static PicoTestFilterProc filterSkip, filterPass, filterSkipPropagate,
    filterPassPropagate;
PicoTestFilterResult filterSkip(PicoTestProc *test, const char *testName,
                                const char *cond) {
    filterCalled++;
    return PICOTEST_FILTER_SKIP;
}
PicoTestFilterResult filterPass(PicoTestProc *test, const char *testName,
                                const char *cond) {
    filterCalled++;
    return PICOTEST_FILTER_PASS;
}
PicoTestFilterResult filterSkipPropagate(PicoTestProc *test,
                                         const char *testName,
                                         const char *cond) {
    filterCalled++;
    return PICOTEST_FILTER_SKIP_PROPAGATE;
}
PicoTestFilterResult filterPassPropagate(PicoTestProc *test,
                                         const char *testName,
                                         const char *cond) {
    filterCalled++;
    return PICOTEST_FILTER_PASS_PROPAGATE;
}

#define NB_SUITES 2
#define NB_CASES 2
#define SUITE_LENGTH (NB_SUITES + NB_CASES)

#undef PICOTEST_FILTER
#define PICOTEST_FILTER filterSkip
PICOTEST_SUITE(doFilterSkipSuite, doFilterSkipCase, doFilterSkipSubsuite)
PICOTEST_SUITE(doFilterSkipSubsuite, doFilterSkipCase)
PICOTEST_CASE(doFilterSkipCase) {
    testCaseCalled++;
}

#undef PICOTEST_FILTER
#define PICOTEST_FILTER filterPass
PICOTEST_SUITE(doFilterPassSuite, doFilterPassCase, doFilterPassSubsuite)
PICOTEST_SUITE(doFilterPassSubsuite, doFilterPassCase)
PICOTEST_CASE(doFilterPassCase) {
    testCaseCalled++;
}

#undef PICOTEST_FILTER
#define PICOTEST_FILTER filterSkipPropagate
PICOTEST_SUITE(doFilterSkipPropagateSuite, doFilterSkipPropagateCase,
               doFilterSkipPropagateSubsuite)
PICOTEST_SUITE(doFilterSkipPropagateSubsuite, doFilterSkipPropagateCase)
PICOTEST_CASE(doFilterSkipPropagateCase) {
    testCaseCalled++;
}

#undef PICOTEST_FILTER
#define PICOTEST_FILTER filterPassPropagate
PICOTEST_SUITE(doFilterPassPropagateSuite, doFilterPassPropagateCase,
               doFilterPassPropagateSubsuite)
PICOTEST_SUITE(doFilterPassPropagateSubsuite, doFilterPassPropagateCase)
PICOTEST_CASE(doFilterPassPropagateCase) {
    testCaseCalled++;
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for filters
 */
#include "hooks.h"

PICOTEST_SUITE(testFilters, testFilterDefaultShouldBypassFilterAndRunWholeSuite,
               testFilterSkipShouldSkipWholeSuite,
               testFilterPassShouldRunWholeSuite,
               testFilterSkipPropagateShouldSkipSuiteAndFilterSubtests,
               testFilterPassPropagateShouldRunSuiteAndFilterSubtests);

PICOTEST_CASE(testFilterDefaultShouldBypassFilterAndRunWholeSuite) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    filterCalled = testCaseCalled = 0;
    doFilterPassSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    filterCalled = testCaseCalled = 0;
    doFilterSkipPropagateSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    filterCalled = testCaseCalled = 0;
    doFilterPassPropagateSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}

/*
 * PICOTEST_FILTER_SKIP
 */

PICOTEST_CASE(testFilterSkipShouldSkipWholeSuite) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipSuite("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}

/*
 * PICOTEST_FILTER_PASS
 */

PICOTEST_CASE(testFilterPassShouldRunWholeSuite) {
    filterCalled = testCaseCalled = 0;
    doFilterPassSuite("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}

/*
 * PICOTEST_FILTER_SKIP_PROPAGATE
 */

PICOTEST_CASE(testFilterSkipPropagateShouldSkipSuiteAndFilterSubtests) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipPropagateSuite("dummy");
    PICOTEST_VERIFY(filterCalled == SUITE_LENGTH);
    PICOTEST_VERIFY(testCaseCalled == 0);
}

/*
 * PICOTEST_FILTER_PASS_PROPAGATE
 */

PICOTEST_CASE(testFilterPassPropagateShouldRunSuiteAndFilterSubtests) {
    filterCalled = testCaseCalled = 0;
    doFilterPassPropagateSuite("dummy");
    PICOTEST_VERIFY(filterCalled == SUITE_LENGTH);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}
