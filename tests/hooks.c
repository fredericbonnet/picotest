#include <stdio.h>

#include <picotest.h>

#include "hooks.h"
#include "json.h"

/* Text format hooks */
static PicoTestFailureLoggerProc logFailureTxt;
static PicoTestSuiteEnterProc enterTestSuiteTxt;
static PicoTestSuiteLeaveProc leaveTestSuiteTxt;
static PicoTestSuiteBeforeSubtestProc beforeSubtestTxt;
static PicoTestSuiteAfterSubtestProc afterSubtestTxt;
static PicoTestCaseEnterProc enterTestCaseTxt;
static PicoTestCaseLeaveProc leaveTestCaseTxt;

/* JSON format hooks */
static PicoTestFailureLoggerProc logFailureJson;
static PicoTestSuiteEnterProc enterTestSuiteJson;
static PicoTestSuiteLeaveProc leaveTestSuiteJson;
static PicoTestSuiteBeforeSubtestProc beforeSubtestJson;
static PicoTestSuiteAfterSubtestProc afterSubtestJson;
static PicoTestCaseEnterProc enterTestCaseJson;
static PicoTestCaseLeaveProc leaveTestCaseJson;

PicoTestFailureLoggerProc *logFailure = NULL;
PicoTestSuiteEnterProc *enterTestSuite = NULL;
PicoTestSuiteLeaveProc *leaveTestSuite = NULL;
PicoTestSuiteBeforeSubtestProc *beforeSubtest = NULL;
PicoTestSuiteAfterSubtestProc *afterSubtest = NULL;
PicoTestCaseEnterProc *enterTestCase = NULL;
PicoTestCaseLeaveProc *leaveTestCase = NULL;

void initHooks(int json) {
    if (json) {
        logFailure = logFailureJson;
        enterTestSuite = enterTestSuiteJson;
        leaveTestSuite = leaveTestSuiteJson;
        beforeSubtest = beforeSubtestJson;
        afterSubtest = afterSubtestJson;
        enterTestCase = enterTestCaseJson;
        leaveTestCase = leaveTestCaseJson;
    } else {
        logFailure = logFailureTxt;
        enterTestSuite = enterTestSuiteTxt;
        leaveTestSuite = leaveTestSuiteTxt;
        beforeSubtest = beforeSubtestTxt;
        afterSubtest = afterSubtestTxt;
        enterTestCase = enterTestCaseTxt;
        leaveTestCase = leaveTestCaseTxt;
    }
}

/*
 * Text hooks
 */

/* Test failure log handler */
static void logFailureTxt(const char *file, int line, const char *type,
                          const char *test, const char *msg, va_list args) {
    printf("\n[%s] %s(%d) : %s", type, file, line, test);
    if (msg) {
        printf(" | ");
        vprintf(msg, args);
    }
    printf("\n");
}

/* Test suite tracing hooks */
static char prefix[256] = "";
static int prefixLength = 0;
static void enterTestSuiteTxt(const char *suiteName, int nb) {
    printf("%s%s (%d subtests) ...\n", prefix, suiteName, nb);
    fflush(stdout);
    prefix[prefixLength++] = ' ';
    prefix[prefixLength] = '\0';
}
static void leaveTestSuiteTxt(const char *suiteName, int nb, int fail) {
    prefix[--prefixLength] = '\0';
    printf("%s%s : %d failed (total)\n", prefix, suiteName, fail);
    fflush(stdout);
}
static void beforeSubtestTxt(const char *suiteName, int nb, int fail, int index,
                             const char *testName) {}
static void afterSubtestTxt(const char *suiteName, int nb, int fail, int index,
                            const char *testName, int sfail) {}

/* Test case tracing hooks */
static void enterTestCaseTxt(const char *testName) {
    printf("%s%s ... ", prefix, testName);
    fflush(stdout);
}
static void leaveTestCaseTxt(const char *testName, int fail) {
    if (fail) {
        printf("failed");
    } else {
        printf("passed");
    }
    printf("\n");
    fflush(stdout);
}

/*
 * JSON hooks
 */

/* Test failure log handler */
static void logFailureJson(const char *file, int line, const char *type,
                           const char *test, const char *msg, va_list args) {
    printf("{");
    printJsonStringMember("hook", "FAILURE");
    printf(",");
    printJsonStringMember("file", file);
    printf(",");
    printJsonIntMember("line", line);
    printf(",");
    printJsonStringMember("type", type);
    printf(",");
    printJsonStringMember("test", test);
    if (msg) {
        char buffer[256];
        printf(",");
        vsnprintf(buffer, sizeof(buffer), msg, args);
        printJsonStringMember("msg", buffer);
    }
    printf("}\n");
}

/* Test suite tracing hooks */
static void enterTestSuiteJson(const char *suiteName, int nb) {
    printf("{");
    printJsonStringMember("hook", "SUITE_ENTER");
    printf(",");
    printJsonStringMember("suiteName", suiteName);
    printf(",");
    printJsonIntMember("nb", nb);
    printf("}\n");
}
static void leaveTestSuiteJson(const char *suiteName, int nb, int fail) {
    printf("{");
    printJsonStringMember("hook", "SUITE_LEAVE");
    printf(",");
    printJsonStringMember("suiteName", suiteName);
    printf(",");
    printJsonIntMember("nb", nb);
    printf(",");
    printJsonIntMember("fail", fail);
    printf("}\n");
}
static void beforeSubtestJson(const char *suiteName, int nb, int fail,
                              int index, const char *testName) {
    printf("{");
    printJsonStringMember("hook", "SUITE_BEFORE_SUBTEST");
    printf(",");
    printJsonStringMember("suiteName", suiteName);
    printf(",");
    printJsonIntMember("nb", nb);
    printf(",");
    printJsonIntMember("fail", fail);
    printf(",");
    printJsonIntMember("index", index);
    printf(",");
    printJsonStringMember("testName", testName);
    printf("}\n");
}
static void afterSubtestJson(const char *suiteName, int nb, int fail, int index,
                             const char *testName, int sfail) {
    printf("{");
    printJsonStringMember("hook", "SUITE_AFTER_SUBTEST");
    printf(",");
    printJsonStringMember("suiteName", suiteName);
    printf(",");
    printJsonIntMember("nb", nb);
    printf(",");
    printJsonIntMember("fail", fail);
    printf(",");
    printJsonIntMember("index", index);
    printf(",");
    printJsonStringMember("testName", testName);
    printf(",");
    printJsonIntMember("sfail", sfail);
    printf("}\n");
}

/* Test case tracing hooks */
static void enterTestCaseJson(const char *testName) {
    printf("{");
    printJsonStringMember("hook", "CASE_ENTER");
    printf(",");
    printJsonStringMember("testName", testName);
    printf("}\n");
}
static void leaveTestCaseJson(const char *testName, int fail) {
    printf("{");
    printJsonStringMember("hook", "CASE_LEAVE");
    printf(",");
    printJsonStringMember("testName", testName);
    printf(",");
    printJsonIntMember("fail", fail);
    printf("}\n");
}
