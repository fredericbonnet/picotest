#include <picotest.h>

/*
 * Test utilities
 */

static int testCaseCalled;
PICOTEST_CASE(doTestCase) {
    testCaseCalled++;
}
PICOTEST_CASE(doTestCaseSuccess) {
    testCaseCalled++;
}
PICOTEST_CASE(doTestCaseFailure) {
    testCaseCalled++;
    PICOTEST_VERIFY(0);
    PICOTEST_FAILURE("FAILURE", "");
    PICOTEST_ASSERT(0);
}

/*
 * Test suite for test cases
 */
#include "hooks.h"

PICOTEST_SUITE(testCases, testCasesShouldBeCallable,
               testCasesShouldReportSuccess, testCasesShouldReportFailures);

PICOTEST_CASE(testCasesShouldBeCallable) {
    testCaseCalled = 0;
    doTestCase(NULL);
    PICOTEST_ASSERT(testCaseCalled == 1);
}
PICOTEST_CASE(testCasesShouldReportSuccess) {
    int fail = doTestCaseSuccess(NULL);
    PICOTEST_ASSERT(fail == 0);
}
PICOTEST_CASE(testCasesShouldReportFailures) {
    int fail = doTestCaseFailure(NULL);
    PICOTEST_ASSERT(fail == 3);
}