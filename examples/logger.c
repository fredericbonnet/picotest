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

/*! [PICOTEST_FAILURE_LOGGER redefinition]. */
/* Custom test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure
/*! [PICOTEST_FAILURE_LOGGER redefinition]. */

/*! [PicoTestFailureLoggerProc example] */
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

/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, testCase3
)

#define FAILS 0
#define PASSES 1

/* Test cases */
PICOTEST_CASE(testCase1) {
    printf("begin testCase1\n");
    PICOTEST_VERIFY(FAILS, "assertion 1"); /* Log error and continue */
    PICOTEST_ASSERT(FAILS, "assertion 2"); /* Log error and abort */
    /* Unreached */
    PICOTEST_ASSERT(PASSES, "assertion 3");
    printf("end testCase1\n");
}
PICOTEST_CASE(testCase2) {
    printf("begin testCase2\n");
    PICOTEST_ASSERT(PASSES, "assertion 1");
    PICOTEST_VERIFY(FAILS, "assertion 2"); /* Log error and continue */
    printf("end testCase2\n");
}
PICOTEST_CASE(testCase3) {
    printf("begin testCase3\n");
    PICOTEST_ASSERT(PASSES, "assertion 1");
    PICOTEST_ABORT();
    /* Unreached */
    PICOTEST_VERIFY(FAILS, "assertion 2");
    printf("end testCase3\n");
}

void main() {
    mainSuite(NULL);
}
/** @endcond */
