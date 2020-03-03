#include <stdio.h>

#include <picotest.h>

#include "hooks.h"

/* Test failure log handler */
void logFailure(const char *file, int line, const char *type, const char *test,
                const char *msg, va_list args) {
    printf("\n[%s] %s(%d) : %s", type, file, line, test);
    if (msg) {
        printf(" | ");
        vprintf(msg, args);
    }
    printf("\n");
}

/* Test tracing hooks */
static char prefix[256] = "";
static int prefixLength = 0;
void enterTestSuite(const char *suiteName, int nb) {
    printf("%s%s (%d subtests) ...\n", prefix, suiteName, nb);
    fflush(stdout);
    prefix[prefixLength++] = ' ';
    prefix[prefixLength] = '\0';
}
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    prefix[--prefixLength] = '\0';
    printf("%s%s : %d failed (total)\n", prefix, suiteName, fail);
    fflush(stdout);
}
void beforeSubtest(const char *suiteName, int nb, int fail, int index,
                   const char *testName) {}
void afterSubtest(const char *suiteName, int nb, int fail, int index,
                  const char *testName, int sfail) {}
void enterTestCase(const char *testName) {
    printf("%s%s ... ", prefix, testName);
    fflush(stdout);
}
void leaveTestCase(const char *testName, int fail) {
    if (fail) {
        printf("failed");
    } else {
        printf("passed");
    }
    printf("\n");
    fflush(stdout);
}
