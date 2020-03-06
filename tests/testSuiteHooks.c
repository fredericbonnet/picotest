#include <picotest.h>

/*
 * Test utilities
 */

#define MAX_LEVELS 5
static struct {
    int step;

    int testSuiteEnterCalled;
    struct {
        int step;
        const char *suiteName;
        int nb;
    } testSuiteEnter[MAX_LEVELS];

    int testSuiteLeaveCalled;
    struct {
        int step;
        const char *suiteName;
        int nb;
        int fail;
    } testSuiteLeave[MAX_LEVELS];

    int testSuiteBeforeSubtestCalled;
    struct {
        int step;
        const char *suiteName;
        int nb;
        int fail;
        int index;
        const char *testName;
    } testSuiteBeforeSubtest[MAX_LEVELS];

    int testSuiteAfterSubtestCalled;
    struct {
        int step;
        const char *suiteName;
        int nb;
        int fail;
        int index;
        const char *testName;
        int sfail;
    } testSuiteAfterSubtest[MAX_LEVELS];
} state;
static void init() {
    memset(&state, 0, sizeof(state));
}

/* Hooks used for testing */
static PicoTestSuiteEnterProc testSuiteEnter;
static PicoTestSuiteLeaveProc testSuiteLeave;
static PicoTestSuiteBeforeSubtestProc testSuiteBeforeSubtest;
static PicoTestSuiteAfterSubtestProc testSuiteAfterSubset;
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_ENTER testSuiteEnter
#define PICOTEST_SUITE_LEAVE testSuiteLeave
#define PICOTEST_SUITE_BEFORE_SUBTEST testSuiteBeforeSubtest
#define PICOTEST_SUITE_AFTER_SUBTEST testSuiteAfterSubset
void testSuiteEnter(const char *suiteName, int nb) {
    int i = state.testSuiteEnterCalled++;
    state.step++;
    if (i < MAX_LEVELS) {
        state.testSuiteEnter[i].step = state.step;
        state.testSuiteEnter[i].suiteName = suiteName;
        state.testSuiteEnter[i].nb = nb;
    }
}
void testSuiteLeave(const char *suiteName, int nb, int fail) {
    int i = state.testSuiteLeaveCalled++;
    state.step++;
    if (i < MAX_LEVELS) {
        state.testSuiteLeave[i].step = state.step;
        state.testSuiteLeave[i].suiteName = suiteName;
        state.testSuiteLeave[i].nb = nb;
        state.testSuiteLeave[i].fail = fail;
    }
}
void testSuiteBeforeSubtest(const char *suiteName, int nb, int fail, int index,
                            const char *testName) {
    int i = state.testSuiteBeforeSubtestCalled++;
    state.step++;
    if (i < MAX_LEVELS) {
        state.testSuiteBeforeSubtest[i].step = state.step;
        state.testSuiteBeforeSubtest[i].suiteName = suiteName;
        state.testSuiteBeforeSubtest[i].nb = nb;
        state.testSuiteBeforeSubtest[i].fail = fail;
        state.testSuiteBeforeSubtest[i].index = index;
        state.testSuiteBeforeSubtest[i].testName = testName;
    }
}
void testSuiteAfterSubset(const char *suiteName, int nb, int fail, int index,
                          const char *testName, int sfail) {
    int i = state.testSuiteAfterSubtestCalled++;
    state.step++;
    if (i < MAX_LEVELS) {
        state.testSuiteAfterSubtest[i].step = state.step;
        state.testSuiteAfterSubtest[i].suiteName = suiteName;
        state.testSuiteAfterSubtest[i].nb = nb;
        state.testSuiteAfterSubtest[i].fail = fail;
        state.testSuiteAfterSubtest[i].index = index;
        state.testSuiteAfterSubtest[i].testName = testName;
        state.testSuiteAfterSubtest[i].sfail = sfail;
    }
}

PICOTEST_SUITE(doHookTestSuite, doHookTestSubsuite, doHookTestCasePass,
               doHookTestCaseFail);
PICOTEST_SUITE(doHookTestSubsuite, doHookTestCaseFail1, doHookTestCaseFail2);
PICOTEST_CASE(doHookTestCasePass) {
    state.step++;
    PICOTEST_ASSERT(1);
    state.step++;
}
PICOTEST_CASE(doHookTestCaseFail) {
    state.step++;
    PICOTEST_VERIFY(0);
    state.step++;
}
PICOTEST_CASE(doHookTestCaseFail1) {
    state.step++;
    PICOTEST_ASSERT(0);
    state.step++;
}
PICOTEST_CASE(doHookTestCaseFail2) {
    state.step++;
    PICOTEST_VERIFY(0);
    PICOTEST_FAILURE("FAILURE", "");
    state.step++;
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for test suite hooks
 */
#include "hooks.h"

PICOTEST_SUITE(testSuiteHooks, testSuiteHooksCallOrder, testSuiteEnterHook,
               testSuiteLeaveHook, testSuiteBeforeSubtestHook,
               testSuiteAfterSubtestHook);

PICOTEST_CASE(testSuiteHooksCallOrder) {
    init();
    doHookTestSuite(NULL);
    PICOTEST_ASSERT(state.testSuiteEnterCalled == 2);
    PICOTEST_ASSERT(state.testSuiteLeaveCalled == 2);
    PICOTEST_ASSERT(state.testSuiteBeforeSubtestCalled == 5);
    PICOTEST_ASSERT(state.testSuiteAfterSubtestCalled == 5);

    PICOTEST_VERIFY(state.testSuiteEnter[0].step == 1);
    {
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[0].step == 2);
        PICOTEST_VERIFY(state.testSuiteEnter[1].step == 3);
        {
            PICOTEST_VERIFY(state.testSuiteBeforeSubtest[1].step == 4);
            /* doHookTestCaseFail1: step 5 */
            PICOTEST_VERIFY(state.testSuiteAfterSubtest[0].step == 6);
            PICOTEST_VERIFY(state.testSuiteBeforeSubtest[2].step == 7);
            /* doHookTestCaseFail2: steps 8 & 9 */
            PICOTEST_VERIFY(state.testSuiteAfterSubtest[1].step == 10);
        }
        PICOTEST_VERIFY(state.testSuiteLeave[0].step == 11);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[2].step == 12);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[3].step == 13);
        /* doHookTestCasePass: steps 14 & 15 */
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[3].step == 16);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[4].step == 17);
        /* doHookTestCaseFail: steps 18 & 19 */
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[4].step == 20);
    }
    PICOTEST_VERIFY(state.testSuiteLeave[1].step == 21);
}

/*
 * PICOTEST_SUITE_ENTER
 */

PICOTEST_CASE(testSuiteEnterHook) {
    init();
    doHookTestSuite(NULL);
    PICOTEST_ASSERT(state.testSuiteEnterCalled == 2);

    PICOTEST_VERIFY(
        strcmp(state.testSuiteEnter[0].suiteName, "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteEnter[0].nb == 3);

    PICOTEST_VERIFY(
        strcmp(state.testSuiteEnter[1].suiteName, "doHookTestSubsuite") == 0);
    PICOTEST_VERIFY(state.testSuiteEnter[1].nb == 2);
}

/*
 * PICOTEST_SUITE_LEAVE
 */

PICOTEST_CASE(testSuiteLeaveHook) {
    init();
    doHookTestSuite(NULL);
    PICOTEST_ASSERT(state.testSuiteLeaveCalled == 2);

    PICOTEST_VERIFY(
        strcmp(state.testSuiteLeave[0].suiteName, "doHookTestSubsuite") == 0);
    PICOTEST_VERIFY(state.testSuiteLeave[0].nb == 2);
    PICOTEST_VERIFY(state.testSuiteLeave[0].fail == 3);

    PICOTEST_VERIFY(
        strcmp(state.testSuiteLeave[1].suiteName, "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteLeave[1].nb == 3);
    PICOTEST_VERIFY(state.testSuiteLeave[1].fail == 4);
}

/*
 * PICOTEST_SUITE_BEFORE_SUBTEST
 */

PICOTEST_CASE(testSuiteBeforeSubtestHook) {
    init();
    doHookTestSuite(NULL);
    PICOTEST_ASSERT(state.testSuiteBeforeSubtestCalled == 5);

    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[0].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[0].nb == 3);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[0].fail == 0);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[0].index == 0);
    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[0].testName,
                           "doHookTestSubsuite") == 0);

    {
        PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[1].suiteName,
                               "doHookTestSubsuite") == 0);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[1].nb == 2);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[1].fail == 0);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[1].index == 0);
        PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[1].testName,
                               "doHookTestCaseFail1") == 0);

        PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[2].suiteName,
                               "doHookTestSubsuite") == 0);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[2].nb == 2);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[2].fail == 1);
        PICOTEST_VERIFY(state.testSuiteBeforeSubtest[2].index == 1);
        PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[2].testName,
                               "doHookTestCaseFail2") == 0);
    }

    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[3].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[3].nb == 3);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[3].fail == 3);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[3].index == 1);
    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[3].testName,
                           "doHookTestCasePass") == 0);

    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[4].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[4].nb == 3);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[4].fail == 3);
    PICOTEST_VERIFY(state.testSuiteBeforeSubtest[4].index == 2);
    PICOTEST_VERIFY(strcmp(state.testSuiteBeforeSubtest[4].testName,
                           "doHookTestCaseFail") == 0);
}

/*
 * PICOTEST_SUITE_AFTER_SUBTEST
 */

PICOTEST_CASE(testSuiteAfterSubtestHook) {
    init();
    doHookTestSuite(NULL);
    PICOTEST_ASSERT(state.testSuiteAfterSubtestCalled == 5);

    {
        PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[0].suiteName,
                               "doHookTestSubsuite") == 0);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[0].nb == 2);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[0].fail == 1);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[0].index == 0);
        PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[0].testName,
                               "doHookTestCaseFail1") == 0);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[0].sfail == 1);

        PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[1].suiteName,
                               "doHookTestSubsuite") == 0);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[1].nb == 2);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[1].fail == 3);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[1].index == 1);
        PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[1].testName,
                               "doHookTestCaseFail2") == 0);
        PICOTEST_VERIFY(state.testSuiteAfterSubtest[1].sfail == 2);
    }

    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[2].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[2].nb == 3);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[2].fail == 3);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[2].index == 0);
    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[2].testName,
                           "doHookTestSubsuite") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[2].sfail == 3);

    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[3].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[3].nb == 3);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[3].fail == 3);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[3].index == 1);
    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[3].testName,
                           "doHookTestCasePass") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[3].sfail == 0);

    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[4].suiteName,
                           "doHookTestSuite") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[4].nb == 3);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[4].fail == 4);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[4].index == 2);
    PICOTEST_VERIFY(strcmp(state.testSuiteAfterSubtest[4].testName,
                           "doHookTestCaseFail") == 0);
    PICOTEST_VERIFY(state.testSuiteAfterSubtest[4].sfail == 1);
}