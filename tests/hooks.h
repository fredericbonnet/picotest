#ifndef _HOOKS_H_
#define _HOOKS_H_

#include <picotest.h>

/* Initialize hooks */
void initHooks(int json);

/* Test failure log handler */
extern PicoTestFailureLoggerProc *logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test suite tracing hooks */
extern PicoTestSuiteEnterProc *enterTestSuite;
extern PicoTestSuiteLeaveProc *leaveTestSuite;
extern PicoTestSuiteBeforeSubtestProc *beforeSubtest;
extern PicoTestSuiteAfterSubtestProc *afterSubtest;
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_ENTER enterTestSuite
#define PICOTEST_SUITE_LEAVE leaveTestSuite
#define PICOTEST_SUITE_BEFORE_SUBTEST beforeSubtest
#define PICOTEST_SUITE_AFTER_SUBTEST afterSubtest

/* Test case tracing hooks */
extern PicoTestCaseEnterProc *enterTestCase;
extern PicoTestCaseLeaveProc *leaveTestCase;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER enterTestCase
#define PICOTEST_CASE_LEAVE leaveTestCase

#endif /* _HOOKS_H_ */
