#include <picotest.h>

/*
 * Test utilities
 */

/* Logger and hooks used for testing */
static int testFailureLoggerCalled;
static PicoTestFailureLoggerProc testFailureLogger;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER testFailureLogger
void testFailureLogger(const char *file, int line, const char *type,
                       const char *test, const char *msg, va_list args) {
    testFailureLoggerCalled = 1;
}

static int testAssertBeforeCalled, testAssertAfterCalled;
static PicoTestAssertBeforeProc testAssertBefore;
static PicoTestAssertAfterProc testAssertAfter;
#undef PICOTEST_ASSERT_BEFORE
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_BEFORE testAssertBefore
#define PICOTEST_ASSERT_AFTER testAssertAfter
void testAssertBefore(const char *type, const char *test) {
    testAssertBeforeCalled = 1;
}
void testAssertAfter(const char *type, const char *test, int fail) {
    testAssertAfterCalled = 1;
}

static int testCaseStep;
PICOTEST_CASE(doAssert) {
    testCaseStep++;
    PICOTEST_ASSERT(0);
    testCaseStep++;
}
PICOTEST_CASE(doVerify) {
    testCaseStep++;
    PICOTEST_VERIFY(0);
    testCaseStep++;
}
PICOTEST_CASE(doFailure) {
    testCaseStep++;
    PICOTEST_FAILURE("FAILURE", 0);
    testCaseStep++;
}
PICOTEST_CASE(doAbort) {
    testCaseStep++;
    PICOTEST_ABORT();
    testCaseStep++;
}

/* Reset default logger and hooks */
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER PICOTEST_FAILURE_LOGGER_DEFAULT

#undef PICOTEST_ASSERT_BEFORE
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_BEFORE PICOTEST_ASSERT_BEFORE_DEFAULT
#define PICOTEST_ASSERT_AFTER PICOTEST_ASSERT_AFTER_DEFAULT

/*
 * Import hooks for test suite
 */

#include "hooks.h"

/*
 * Test suite for assertions
 */

PICOTEST_SUITE(testAssertions, testAssert, testVerify, testFailure, testAbort);

/*
 * PICOTEST_ASSERT
 */

PICOTEST_SUITE(testAssert, testAssertShouldFail, testAssertShouldAbortTest,
               testAssertShouldCallFailureLogger,
               testAssertShouldCallAssertHooks);

PICOTEST_CASE(testAssertShouldFail) {
    int fail = doAssert(NULL);
    PICOTEST_ASSERT(fail == 1);
}
PICOTEST_CASE(testAssertShouldAbortTest) {
    testCaseStep = 0;
    doAssert(NULL);
    PICOTEST_ASSERT(testCaseStep == 1);
}
PICOTEST_CASE(testAssertShouldCallFailureLogger) {
    testFailureLoggerCalled = 0;
    doAssert(NULL);
    PICOTEST_ASSERT(testFailureLoggerCalled == 1);
}
PICOTEST_CASE(testAssertShouldCallAssertHooks) {
    testAssertBeforeCalled = testAssertAfterCalled = 0;
    doAssert(NULL);
    PICOTEST_ASSERT(testAssertBeforeCalled == 1);
    PICOTEST_ASSERT(testAssertAfterCalled == 1);
}

/*
 * PICOTEST_VERIFY
 */

PICOTEST_SUITE(testVerify, testVerifyShouldFail, testVerifyShouldContinueTest,
               testVerifyShouldCallFailureLogger,
               testVerifyShouldCallAssertHooks);

PICOTEST_CASE(testVerifyShouldFail) {
    int fail = doVerify(NULL);
    PICOTEST_ASSERT(fail == 1);
}
PICOTEST_CASE(testVerifyShouldContinueTest) {
    testCaseStep = 0;
    doVerify(NULL);
    PICOTEST_ASSERT(testCaseStep == 2);
}
PICOTEST_CASE(testVerifyShouldCallFailureLogger) {
    testFailureLoggerCalled = 0;
    doVerify(NULL);
    PICOTEST_ASSERT(testFailureLoggerCalled == 1);
}
PICOTEST_CASE(testVerifyShouldCallAssertHooks) {
    testAssertBeforeCalled = testAssertAfterCalled = 0;
    doVerify(NULL);
    PICOTEST_ASSERT(testAssertBeforeCalled == 1);
    PICOTEST_ASSERT(testAssertAfterCalled == 1);
}

/*
 * PICOTEST_FAILURE
 */

PICOTEST_SUITE(testFailure, testFailureShouldFail,
               testFailureShouldContinueTest,
               testFailureShouldCallFailureLogger,
               testFailureShouldNotCallAssertHooks);

PICOTEST_CASE(testFailureShouldFail) {
    int fail = doFailure(NULL);
    PICOTEST_ASSERT(fail == 1);
}
PICOTEST_CASE(testFailureShouldContinueTest) {
    testCaseStep = 0;
    doFailure(NULL);
    PICOTEST_ASSERT(testCaseStep == 2);
}
PICOTEST_CASE(testFailureShouldCallFailureLogger) {
    testFailureLoggerCalled = 0;
    doFailure(NULL);
    PICOTEST_ASSERT(testFailureLoggerCalled == 1);
}
PICOTEST_CASE(testFailureShouldNotCallAssertHooks) {
    testAssertBeforeCalled = testAssertAfterCalled = 0;
    doFailure(NULL);
    PICOTEST_ASSERT(testAssertBeforeCalled == 0);
    PICOTEST_ASSERT(testAssertAfterCalled == 0);
}

/*
 * PICOTEST_ABORT
 */

PICOTEST_SUITE(testAbort, testAbortShouldNotFail, testAbortShouldAbortTest,
               testAbortShouldNotCallFailureLogger,
               testAbortShouldNotCallAssertHooks);

PICOTEST_CASE(testAbortShouldNotFail) {
    int fail = doAbort(NULL);
    PICOTEST_ASSERT(fail == 0);
}
PICOTEST_CASE(testAbortShouldAbortTest) {
    testCaseStep = 0;
    doAbort(NULL);
    PICOTEST_ASSERT(testCaseStep == 1);
}
PICOTEST_CASE(testAbortShouldNotCallFailureLogger) {
    testFailureLoggerCalled = 0;
    doAbort(NULL);
    PICOTEST_ASSERT(testFailureLoggerCalled == 0);
}
PICOTEST_CASE(testAbortShouldNotCallAssertHooks) {
    testAssertBeforeCalled = testAssertAfterCalled = 0;
    doAbort(NULL);
    PICOTEST_ASSERT(testAssertBeforeCalled == 0);
    PICOTEST_ASSERT(testAssertAfterCalled == 0);
}
