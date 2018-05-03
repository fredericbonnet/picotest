/**
 * @file logger.c
 * 
 * Example of PicoTest error logging, prints location and info of failed 
 * assertions to stdout.
 *
 * @include logger.c
 * @cond IGNORE 
 */
#include <stdio.h>
#include <picotest.h>

/*! [PicoTestFailureLoggerProc example] */
/* Custom test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Custom test failure logger definition. */
void logFailure(const char *file, int line, const char *type, const char *test, const char *msg, va_list args) {
    /* Error type. */
    printf("[%s] ", type);

    /* Location in source code. */
    printf("%s(%d) : ", file, line);

    /* Failed expression. */
    printf("%s", test);

    /* Optional message. */
    if (msg) {
        printf(" | "); 
        vprintf(msg, args);
    }

    printf("\n");
}
/*! [PicoTestFailureLoggerProc example] */

/* Hooks */
PicoTestCaseEnterProc logEnter;
PicoTestCaseLeaveProc logLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER logEnter
#define PICOTEST_CASE_LEAVE logLeave

void logEnter(const char *name) {
    printf("begin %s\n", name);
}
void logLeave(const char *name, int fail) {
    if (!fail) printf("end %s\n", name);
}

/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, testCase3
)

#define FAILS 0
#define PASSES 1

/* Test cases */
PICOTEST_CASE(testCase1) {
    PICOTEST_VERIFY(FAILS, "assertion 1"); /* Log error and continue */
    PICOTEST_ASSERT(FAILS, "assertion 2"); /* Log error and abort */
    /* Unreached */
    PICOTEST_ASSERT(PASSES, "assertion 3");
}
PICOTEST_CASE(testCase2) {
    PICOTEST_ASSERT(PASSES, "assertion 1");
    PICOTEST_VERIFY(FAILS, "assertion 2"); /* Log error and continue */
}
PICOTEST_CASE(testCase3) {
    PICOTEST_ASSERT(PASSES, "assertion 1");
    PICOTEST_ABORT();
    /* Unreached */
    PICOTEST_VERIFY(FAILS, "assertion 2");
}

void main() {
    mainSuite(NULL);
}
/** @endcond */
