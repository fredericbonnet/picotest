#include <picotest.h>

/*
 * Test utilities
 */

static struct {
    int testCaseStep;
    int testFailureLoggerCalled;
    int testCaseEnterCalled;
    int testCaseLeaveCalled;
    const char *testCaseEnterTestName;
    const char *testCaseLeaveTestName;
    int testCaseLeaveFail;
} state;
static void init() {
    memset(&state, 0, sizeof(state));
}

/* Logger and hooks used for testing */
static PicoTestFailureLoggerProc testFailureLogger;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER testFailureLogger
void testFailureLogger(const char *file, int line, const char *type,
                       const char *test, const char *msg, va_list args) {
    state.testFailureLoggerCalled = ++state.testCaseStep;
}

static PicoTestCaseEnterProc testCaseEnter;
static PicoTestCaseLeaveProc testCaseLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER testCaseEnter
#define PICOTEST_CASE_LEAVE testCaseLeave
void testCaseEnter(const char *testName) {
    state.testCaseEnterCalled = ++state.testCaseStep;
    state.testCaseEnterTestName = testName;
}
void testCaseLeave(const char *testName, int fail) {
    state.testCaseLeaveCalled = ++state.testCaseStep;
    state.testCaseLeaveTestName = testName;
    state.testCaseLeaveFail = fail;
}

PICOTEST_CASE(doPass) {
    state.testCaseStep++;
    PICOTEST_VERIFY(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFail) {
    state.testCaseStep++;
    PICOTEST_VERIFY(0);
    state.testCaseStep++;
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for test case hooks
 */
#include "hooks.h"

PICOTEST_SUITE(testCaseHooks, testCaseHooksCallOrder, testCaseEnterHook,
               testCaseLeaveHook);

PICOTEST_SUITE(testCaseHooksCallOrder, testCaseHooksCallOrderPass,
               testCaseHooksCallOrderFail)
PICOTEST_CASE(testCaseHooksCallOrderPass) {
    init();
    doPass(NULL);
    PICOTEST_VERIFY(state.testCaseEnterCalled == 1);
    PICOTEST_VERIFY(state.testFailureLoggerCalled == 0);
    PICOTEST_VERIFY(state.testCaseLeaveCalled == 4);
}
PICOTEST_CASE(testCaseHooksCallOrderFail) {
    init();
    doFail(NULL);
    PICOTEST_VERIFY(state.testCaseEnterCalled == 1);
    PICOTEST_VERIFY(state.testFailureLoggerCalled == 3);
    PICOTEST_VERIFY(state.testCaseLeaveCalled == 5);
}

/*
 * PICOTEST_CASE_ENTER
 */

PICOTEST_CASE(testCaseEnterHook) {
    init();
    doPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testCaseEnterTestName, "doPass") == 0);

    init();
    doFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testCaseEnterTestName, "doFail") == 0);
}

/*
 * PICOTEST_CASE_LEAVE
 */

PICOTEST_CASE(testCaseLeaveHook) {
    init();
    doPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testCaseLeaveTestName, "doPass") == 0);
    PICOTEST_VERIFY(state.testCaseLeaveFail == 0);

    init();
    doFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testCaseLeaveTestName, "doFail") == 0);
    PICOTEST_VERIFY(state.testCaseLeaveFail == 1);
}
