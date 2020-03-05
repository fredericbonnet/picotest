#include <picotest.h>

/*
 * Test utilities
 */

/* Filters and hooks used for testing */
static int filterCalled, testCaseCalled;
static struct {
    PicoTestProc *test;
    const char *testName;
    const char *cond;
} args;
static void init() {
    filterCalled = testCaseCalled = 0;
    memset(&args, 0, sizeof(args));
}
static PicoTestFilterProc filterArgs, filterSkip, filterPass,
    filterSkipPropagate, filterPassPropagate;
PicoTestFilterResult filterArgs(PicoTestProc *test, const char *testName,
                                const char *cond) {
    args.test = test;
    args.testName = testName;
    args.cond = cond;
    return PICOTEST_FILTER_PASS;
}
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

#undef PICOTEST_FILTER
#define PICOTEST_FILTER filterArgs
PICOTEST_CASE(doFilterArgs) {
    testCaseCalled++;
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

PICOTEST_SUITE(testFilters, testFilterArguments, testFilterNoCondition,
               testFilterSkip, testFilterPass, testFilterSkipPropagate,
               testFilterPassPropagate);

/*
 * Arguments
 */

PICOTEST_CASE(testFilterArguments) {
    init();
    doFilterArgs("condition");
    PICOTEST_VERIFY(args.test == doFilterArgs);
    PICOTEST_VERIFY(strcmp(args.testName, "doFilterArgs") == 0);
    PICOTEST_VERIFY(strcmp(args.cond, "condition") == 0);
}

/*
 * No condition
 */

PICOTEST_SUITE(testFilterNoCondition,
               testFilterNoConditionShouldBypassFilterAndRunCase,
               testFilterNoConditionShouldBypassFilterAndRunWholeSuite);

PICOTEST_CASE(testFilterNoConditionShouldBypassFilterAndRunCase) {
    init();
    doFilterSkipCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0)
    PICOTEST_VERIFY(testCaseCalled == 1);

    init();
    doFilterPassCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);

    init();
    doFilterSkipPropagateCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);

    init();
    doFilterPassPropagateCase(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterNoConditionShouldBypassFilterAndRunWholeSuite) {
    init();
    doFilterSkipSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    init();
    doFilterPassSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    init();
    doFilterSkipPropagateSuite(NULL);
    PICOTEST_VERIFY(filterCalled == 0);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);

    init();
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
    init();
    doFilterSkipCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}
PICOTEST_CASE(testFilterSkipShouldSkipWholeSuite) {
    init();
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
    init();
    doFilterPassCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterPassShouldRunWholeSuite) {
    init();
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
    init();
    doFilterSkipPropagateCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 0);
}
PICOTEST_CASE(testFilterSkipPropagateShouldSkipSuiteAndFilterSubtests) {
    init();
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
    init();
    doFilterPassPropagateCase("dummy");
    PICOTEST_VERIFY(filterCalled == 1);
    PICOTEST_VERIFY(testCaseCalled == 1);
}
PICOTEST_CASE(testFilterPassPropagateShouldRunSuiteAndFilterSubtests) {
    init();
    doFilterPassPropagateSuite("dummy");
    PICOTEST_VERIFY(filterCalled == SUITE_LENGTH);
    PICOTEST_VERIFY(testCaseCalled == NB_CASES);
}
