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

PICOTEST_SUITE(testFilters, testFilterNoCondition, testFilterSkip,
               testFilterPass, testFilterSkipPropagate,
               testFilterPassPropagate);

/*
 * No condition
 */

PICOTEST_SUITE(testFilterNoCondition,
               testFilterNoConditionShouldBypassFilterAndRunCase,
               testFilterNoConditionShouldBypassFilterAndRunWholeSuite);

PICOTEST_CASE(testFilterNoConditionShouldBypassFilterAndRunCase) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0)
    PICOTEST_VERIFY(testCaseCalled == 1);

    filterCalled = testCaseCalled = 0;
    doFilterPassCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);

    filterCalled = testCaseCalled = 0;
    doFilterSkipPropagateCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);

    filterCalled = testCaseCalled = 0;
    doFilterPassPropagateCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterNoConditionShouldBypassFilterAndRunWholeSuite) {
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

PICOTEST_SUITE(testFilterSkip, testFilterSkipShouldSkipCase,
               testFilterSkipShouldSkipWholeSuite);

PICOTEST_CASE(testFilterSkipShouldSkipCase) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}
PICOTEST_CASE(testFilterSkipShouldSkipWholeSuite) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipSuite("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}

/*
 * PICOTEST_FILTER_PASS
 */

PICOTEST_SUITE(testFilterPass, testFilterPassShouldRunCase,
               testFilterPassShouldRunWholeSuite);

PICOTEST_CASE(testFilterPassShouldRunCase) {
    filterCalled = testCaseCalled = 0;
    doFilterPassCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterPassShouldRunWholeSuite) {
    filterCalled = testCaseCalled = 0;
    doFilterPassSuite("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}

/*
 * PICOTEST_FILTER_SKIP_PROPAGATE
 */

PICOTEST_SUITE(testFilterSkipPropagate, testFilterSkipPropagateShouldSkipCase,
               testFilterSkipPropagateShouldSkipSuiteAndFilterSubtests);

PICOTEST_CASE(testFilterSkipPropagateShouldSkipCase) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipPropagateCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}
PICOTEST_CASE(testFilterSkipPropagateShouldSkipSuiteAndFilterSubtests) {
    filterCalled = testCaseCalled = 0;
    doFilterSkipPropagateSuite("dummy");
    PICOTEST_VERIFY(filterCalled == SUITE_LENGTH);
    PICOTEST_VERIFY(testCaseCalled == 0);
}

/*
 * PICOTEST_FILTER_PASS_PROPAGATE
 */

PICOTEST_SUITE(testFilterPassPropagate, testFilterPassPropagateShouldRunCase,
               testFilterPassPropagateShouldRunSuiteAndFilterSubtests);

PICOTEST_CASE(testFilterPassPropagateShouldRunCase) {
    filterCalled = testCaseCalled = 0;
    doFilterPassPropagateCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterPassPropagateShouldRunSuiteAndFilterSubtests) {
    filterCalled = testCaseCalled = 0;
    doFilterPassPropagateSuite("dummy");
    PICOTEST_VERIFY(filterCalled == SUITE_LENGTH);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}
