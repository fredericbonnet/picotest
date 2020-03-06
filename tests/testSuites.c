#include <picotest.h>

/*
 * Test utilities
 */

static int testCaseCalled;
PICOTEST_SUITE(doTestSuite, doTestSubsuite, doTestCasePass);
PICOTEST_SUITE(doTestSubsuite, doTestCaseFail1, doTestCaseFail2);
PICOTEST_CASE(doTestCasePass) {
    testCaseCalled++;
    PICOTEST_ASSERT(1);
}
PICOTEST_CASE(doTestCaseFail1) {
    testCaseCalled++;
    PICOTEST_ASSERT(0);
}
PICOTEST_CASE(doTestCaseFail2) {
    testCaseCalled++;
    PICOTEST_VERIFY(0);
    PICOTEST_FAILURE("FAILURE", "");
}

/*
 * Test suite for test suites
 */
#include "hooks.h"

PICOTEST_SUITE(testSuites, testSuitesShouldBeCallable,
               testSuitesShouldReportSubtestFailures);

PICOTEST_CASE(testSuitesShouldBeCallable) {
    testCaseCalled = 0;
    doTestSuite(NULL);
    PICOTEST_ASSERT(testCaseCalled == 3);

    testCaseCalled = 0;
    doTestSubsuite(NULL);
    PICOTEST_ASSERT(testCaseCalled == 2);
}
PICOTEST_CASE(testSuitesShouldReportSubtestFailures) {
    int fail, failSubtests;

    fail = doTestSuite(NULL);
    failSubtests = doTestSubsuite(NULL) + doTestCasePass(NULL);
    PICOTEST_VERIFY(fail == failSubtests);

    fail = doTestSubsuite(NULL);
    failSubtests = doTestCaseFail1(NULL) + doTestCaseFail2(NULL);
    PICOTEST_VERIFY(fail == failSubtests);
}