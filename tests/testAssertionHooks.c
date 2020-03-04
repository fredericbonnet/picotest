#include <picotest.h>

/*
 * Test utilities
 */

static struct {
    int testCaseStep;
    int testFailureLoggerCalled;
    int testAssertBeforeCalled;
    int testAssertAfterCalled;
    int testAssertAfterFail;
    int testAssertCalled;
    const char *testAssertBeforeType;
    const char *testAssertAfterType;
    const char *testAssertBeforeTest;
    const char *testAssertAfterTest;
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

static PicoTestAssertBeforeProc testAssertBefore;
static PicoTestAssertAfterProc testAssertAfter;
#undef PICOTEST_ASSERT_BEFORE
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_BEFORE testAssertBefore
#define PICOTEST_ASSERT_AFTER testAssertAfter
void testAssertBefore(const char *type, const char *test) {
    state.testAssertBeforeCalled = ++state.testCaseStep;
    state.testAssertBeforeType = type;
    state.testAssertBeforeTest = test;
}
void testAssertAfter(const char *type, const char *test, int fail) {
    state.testAssertAfterCalled = ++state.testCaseStep;
    state.testAssertAfterType = type;
    state.testAssertAfterTest = test;
    state.testAssertAfterFail = fail;
}

static int pass() {
    state.testAssertCalled = ++state.testCaseStep;
    return 1;
}
static int fail() {
    state.testAssertCalled = ++state.testCaseStep;
    return 0;
}
PICOTEST_CASE(doAssertPass) {
    state.testCaseStep++;
    PICOTEST_ASSERT(pass());
    state.testCaseStep++;
}
PICOTEST_CASE(doVerifyPass) {
    state.testCaseStep++;
    PICOTEST_VERIFY(pass());
    state.testCaseStep++;
}
PICOTEST_CASE(doAssertFail) {
    state.testCaseStep++;
    PICOTEST_ASSERT(fail());
    state.testCaseStep++;
}
PICOTEST_CASE(doVerifyFail) {
    state.testCaseStep++;
    PICOTEST_VERIFY(fail());
    state.testCaseStep++;
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for assertion hooks
 */
#include "hooks.h"

PICOTEST_SUITE(testAssertionHooks, testAssertionHooksCallOrder,
               testAssertBeforeHook, testAssertAfterHook);

PICOTEST_SUITE(testAssertionHooksCallOrder, testAssertionHooksCallOrderPass,
               testAssertionHooksCallOrderFail)
PICOTEST_CASE(testAssertionHooksCallOrderPass) {
    init();
    doAssertPass(NULL);
    PICOTEST_VERIFY(state.testAssertBeforeCalled == 2);
    PICOTEST_VERIFY(state.testAssertCalled == 3);
    PICOTEST_VERIFY(state.testAssertAfterCalled == 4);
    PICOTEST_VERIFY(state.testFailureLoggerCalled == 0);
}
PICOTEST_CASE(testAssertionHooksCallOrderFail) {
    init();
    doAssertFail(NULL);
    PICOTEST_VERIFY(state.testAssertBeforeCalled == 2);
    PICOTEST_VERIFY(state.testAssertCalled == 3);
    PICOTEST_VERIFY(state.testAssertAfterCalled == 4);
    PICOTEST_VERIFY(state.testFailureLoggerCalled == 5);
}

/*
 * PICOTEST_ASSERT_BEFORE
 */

PICOTEST_CASE(testAssertBeforeHook) {
    init();
    doAssertPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeType, "ASSERT") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeTest, "pass()") == 0);

    init();
    doAssertFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeType, "ASSERT") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeTest, "fail()") == 0);

    init();
    doVerifyPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeType, "VERIFY") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeTest, "pass()") == 0);

    init();
    doVerifyFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeType, "VERIFY") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertBeforeTest, "fail()") == 0);
}

/*
 * PICOTEST_ASSERT_AFTER
 */

PICOTEST_CASE(testAssertAfterHook) {
    init();
    doAssertPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterType, "ASSERT") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterTest, "pass()") == 0);
    PICOTEST_VERIFY(state.testAssertAfterFail == 0);

    init();
    doAssertFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterType, "ASSERT") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterTest, "fail()") == 0);
    PICOTEST_VERIFY(state.testAssertAfterFail != 0);

    init();
    doVerifyPass(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterType, "VERIFY") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterTest, "pass()") == 0);
    PICOTEST_VERIFY(state.testAssertAfterFail == 0);

    init();
    doVerifyFail(NULL);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterType, "VERIFY") == 0);
    PICOTEST_VERIFY(strcmp(state.testAssertAfterTest, "fail()") == 0);
    PICOTEST_VERIFY(state.testAssertAfterFail != 0);
}
