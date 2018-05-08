/**
 * @file hooks.c
 * 
 * Example of PicoTest hooks, prints all events to stdout.
 *
 * @include hooks.c
 * @cond IGNORE 
 */
#include <stdio.h>
#include <picotest.h>

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}

/*
 * Test suite hooks.
 */

/*! [PICOTEST_SUITE_ENTER example] */
/* Hook declarations. */
PicoTestSuiteEnterProc enterTestSuite;
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER enterTestSuite

/* Hook function. */
void enterTestSuite(const char *suiteName, int nb) {
    indent(level++);
    printf("running test suite %s (%d subtests)...\n", suiteName, nb);
}
/*! [PICOTEST_SUITE_ENTER example] */


/*! [PICOTEST_SUITE_LEAVE example] */
/* Hook declarations. */
PicoTestSuiteLeaveProc leaveTestSuite;
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_SUITE_LEAVE leaveTestSuite

/* Hook function. */
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    indent(--level);
    printf("test suite %s done (%d failures)\n", suiteName, fail);
}
/*! [PICOTEST_SUITE_LEAVE example] */


/*! [PICOTEST_SUITE_BEFORE_SUBTEST example] */
/* Hook declarations. */
PicoTestSuiteBeforeSubtestProc beforeSubtest;
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#define PICOTEST_SUITE_BEFORE_SUBTEST beforeSubtest

/* Hook function. */
void beforeSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName) {
    indent(level++);
    printf("subtest %s (%d out of %d)...\n", testName, index+1, nb);
}
/*! [PICOTEST_SUITE_BEFORE_SUBTEST example] */


/*! [PICOTEST_SUITE_AFTER_SUBTEST example] */
/* Hook declarations. */
PicoTestSuiteAfterSubtestProc afterSubtest;
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_AFTER_SUBTEST afterSubtest

/* Hook function. */
void afterSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName, int sfail) {
    indent(--level);
    printf("=> subtest %s done (%d failed)...\n", testName, sfail);
}
/*! [PICOTEST_SUITE_AFTER_SUBTEST example] */


/*
 * Test fixture hooks.
 */

/*! [PICOTEST_FIXTURE_BEFORE_SETUP example] */
/* Hook declarations. */
PicoTestFixtureBeforeSetupProc beforeSetup;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#define PICOTEST_FIXTURE_BEFORE_SETUP beforeSetup

/* Hook function. */
void beforeSetup(const char *fixtureName, const char *testName) {
    indent(level++);
    printf("fixture %s setup...", fixtureName);
}
/*! [PICOTEST_FIXTURE_BEFORE_SETUP example] */


/*! [PICOTEST_FIXTURE_AFTER_SETUP example] */
/* Hook declarations. */
PicoTestFixtureAfterSetupProc afterSetup;
#undef PICOTEST_FIXTURE_AFTER_SETUP
#define PICOTEST_FIXTURE_AFTER_SETUP afterSetup

/* Hook function. */
void afterSetup(const char *fixtureName, const char *testName) {
    printf(" done\n");
    --level;
}
/*! [PICOTEST_FIXTURE_AFTER_SETUP example] */


/*! [PICOTEST_FIXTURE_BEFORE_TEARDOWN example] */
/* Hook declarations. */
PicoTestFixtureBeforeTeardownProc beforeTeardown;
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN beforeTeardown

/* Hook function. */
void beforeTeardown(const char *fixtureName, const char *testName, int fail) {
    indent(level++);
    printf("fixture %s teardown...", fixtureName);
}
/*! [PICOTEST_FIXTURE_BEFORE_TEARDOWN example] */


/*! [PICOTEST_FIXTURE_AFTER_TEARDOWN example] */
/* Hook declarations. */
PicoTestFixtureAfterTeardownProc afterTeardown;
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_AFTER_TEARDOWN afterTeardown

/* Hook function. */
void afterTeardown(const char *fixtureName, const char *testName, int fail) {
    printf(" done\n");
    --level;
}
/*! [PICOTEST_FIXTURE_AFTER_TEARDOWN example] */


/*
 * Test case hooks.
 */

/*! [PICOTEST_CASE_ENTER example] */
/* Hook declarations. */
PicoTestCaseEnterProc enterTestCase;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER enterTestCase

/* Hook function. */
void enterTestCase(const char *testName) {
    indent(level++);
    printf("running test case %s...\n", testName);
}
/*! [PICOTEST_CASE_ENTER example] */


/*! [PICOTEST_CASE_LEAVE example] */
/* Hook declarations. */
PicoTestCaseLeaveProc leaveTestCase;
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_LEAVE leaveTestCase

/* Hook function. */
void leaveTestCase(const char *testName, int fail) {
    indent(--level);
    printf("test case %s done (%d failures)\n", testName, fail);
}
/*! [PICOTEST_CASE_LEAVE example] */


/* Main test suite */
#include "mainSuite.inc"

void main() {
    mainSuite(NULL);
}
/** @endcond */
