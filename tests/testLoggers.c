#include <stdio.h>

#include <picotest.h>

/*
 * Test utilities
 */

#define MAX_MSG_SIZE 256
#define MAX_LOGS 4
static int nbLogs;
static struct {
    const char *file;
    int line;
    const char *type;
    const char *test;
    const char *msg;
    char msgPrinted[MAX_MSG_SIZE];
} logs[MAX_LOGS];
static void init() {
    nbLogs = 0;
    memset(&logs, 0, sizeof(logs));
}

/* Logger used for testing */
static PicoTestFailureLoggerProc testFailureLogger;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER testFailureLogger
void testFailureLogger(const char *file, int line, const char *type,
                       const char *test, const char *msg, va_list args) {
    int i = nbLogs++;
    if (i < MAX_LOGS) {
        logs[i].file = file;
        logs[i].line = line;
        logs[i].type = type;
        logs[i].test = test;
        logs[i].msg = msg;
        if (msg) {
            vsnprintf(logs[i].msgPrinted, MAX_MSG_SIZE, msg, args);
        } else {
            *(logs[i].msgPrinted) = '\0';
        }
    }
}

PICOTEST_CASE(doLogPass) {}
PICOTEST_CASE(doLogFail) {
    PICOTEST_ASSERT(0);
}
PICOTEST_CASE(doLogFailMultiple) {
    PICOTEST_VERIFY(0 != 0);
    PICOTEST_FAILURE("FAILURE", "1 != 1");
    PICOTEST_ASSERT(2 != 2);
}
static int failureLine;
PICOTEST_CASE(doLogLocation) {
    failureLine = __LINE__, PICOTEST_FAILURE("FAILURE_TYPE", "FAILURE_TEST");
}
PICOTEST_CASE(doLogMessage) {
    PICOTEST_ASSERT(0, "message string %s %d", "one", 2);
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for loggers
 */
#include "hooks.h"

PICOTEST_SUITE(testLoggers, testLoggerShouldNotBeCalledOnSuccess,
               testLoggerShouldBeCalledOnFailure,
               testLoggerShouldGetFailureType,
               testLoggerShouldGetFailedTestBody,
               testLoggerShouldGetFailureLocation,
               testLoggerShouldGetFailureMessage);

PICOTEST_CASE(testLoggerShouldNotBeCalledOnSuccess) {
    init();
    doLogPass(NULL);
    PICOTEST_ASSERT(nbLogs == 0);
}
PICOTEST_CASE(testLoggerShouldBeCalledOnFailure) {
    init();
    doLogFail(NULL);
    PICOTEST_ASSERT(nbLogs == 1);
}
PICOTEST_CASE(testLoggerShouldGetFailureType) {
    init();
    doLogFailMultiple(NULL);
    PICOTEST_ASSERT(nbLogs == 3);
    PICOTEST_VERIFY(strcmp(logs[0].type, "VERIFY") == 0);
    PICOTEST_VERIFY(strcmp(logs[1].type, "FAILURE") == 0);
    PICOTEST_VERIFY(strcmp(logs[2].type, "ASSERT") == 0);
}
PICOTEST_CASE(testLoggerShouldGetFailedTestBody) {
    init();
    doLogFailMultiple(NULL);
    PICOTEST_ASSERT(nbLogs == 3);
    PICOTEST_VERIFY(strcmp(logs[0].test, "0 != 0") == 0);
    PICOTEST_VERIFY(strcmp(logs[1].test, "1 != 1") == 0);
    PICOTEST_VERIFY(strcmp(logs[2].test, "2 != 2") == 0);
}
PICOTEST_CASE(testLoggerShouldGetFailureLocation) {
    init();
    doLogLocation(NULL);
    PICOTEST_ASSERT(nbLogs == 1);
    PICOTEST_VERIFY(strcmp(logs[0].file, __FILE__) == 0);
    PICOTEST_VERIFY(logs[0].line == failureLine);
}
PICOTEST_CASE(testLoggerShouldGetFailureMessage) {
    init();
    doLogMessage(NULL);
    PICOTEST_ASSERT(nbLogs == 1);
    PICOTEST_VERIFY(strcmp(logs[0].msg, "message string %s %d") == 0);
    PICOTEST_VERIFY(strcmp(logs[0].msgPrinted, "message string one 2") == 0);
}