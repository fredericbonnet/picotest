<a id="hooks_8c"></a>
# File hooks.c

![][C++]

**Location**: `examples/hooks.c`

Example of PicoTest hooks, prints all events to stdout.

```cpp

#include <stdio.h>
#include <picotest.h>

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}

/*
 * Test suite hooks.
 */

/* Hook declarations. */
PicoTestSuiteEnterProc enterTestSuite;
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER enterTestSuite

/* Hook function. */
void enterTestSuite(const char *suiteName, int nb) {
    indent(level++);
    printf("running test suite %s (%d subtests)...\n", suiteName, nb);
}


/* Hook declarations. */
PicoTestSuiteLeaveProc leaveTestSuite;
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_SUITE_LEAVE leaveTestSuite

/* Hook function. */
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    indent(--level);
    printf("test suite %s done (%d failures)\n", suiteName, fail);
}


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


/*
 * Test fixture hooks.
 */

/* Hook declarations. */
PicoTestFixtureBeforeSetupProc beforeSetup;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#define PICOTEST_FIXTURE_BEFORE_SETUP beforeSetup

/* Hook function. */
void beforeSetup(const char *fixtureName, const char *testName) {
    indent(level++);
    printf("fixture %s setup...", fixtureName);
}


/* Hook declarations. */
PicoTestFixtureAfterSetupProc afterSetup;
#undef PICOTEST_FIXTURE_AFTER_SETUP
#define PICOTEST_FIXTURE_AFTER_SETUP afterSetup

/* Hook function. */
void afterSetup(const char *fixtureName, const char *testName) {
    printf(" done\n");
    --level;
}


/* Hook declarations. */
PicoTestFixtureBeforeTeardownProc beforeTeardown;
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN beforeTeardown

/* Hook function. */
void beforeTeardown(const char *fixtureName, const char *testName, int fail) {
    indent(level++);
    printf("fixture %s teardown...", fixtureName);
}


/* Hook declarations. */
PicoTestFixtureAfterTeardownProc afterTeardown;
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_AFTER_TEARDOWN afterTeardown

/* Hook function. */
void afterTeardown(const char *fixtureName, const char *testName, int fail) {
    printf(" done\n");
    --level;
}


/*
 * Test case hooks.
 */

/* Hook declarations. */
PicoTestCaseEnterProc enterTestCase;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER enterTestCase

/* Hook function. */
void enterTestCase(const char *testName) {
    indent(level++);
    printf("running test case %s...\n", testName);
}


/* Hook declarations. */
PicoTestCaseLeaveProc leaveTestCase;
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_LEAVE leaveTestCase

/* Hook function. */
void leaveTestCase(const char *testName, int fail) {
    indent(--level);
    printf("test case %s done (%d failures)\n", testName, fail);
}


/*
 * Assertion hooks.
 */

/* Hook declarations. */
PicoTestAssertBeforeProc beforeAssert;
#undef PICOTEST_ASSERT_BEFORE
#define PICOTEST_ASSERT_BEFORE beforeAssert

/* Hook function. */
void beforeAssert(const char *type, const char *test) {
    indent(level++);
    printf("before assertion %s(%s)...\n", type, test);
}


/* Hook declarations. */
PicoTestAssertAfterProc afterAssert;
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_AFTER afterAssert

/* Hook function. */
void afterAssert(const char *type, const char *test, int fail) {
    indent(--level);
    printf("after assertion %s(%s) => %s\n", type, test, fail ? "fails" : "passes");
}


/* Main test suite */
#include "mainSuite.inc"

void main() {
    mainSuite(NULL);
}
```

## Source


```cpp

#include <stdio.h>
#include <picotest.h>

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}

/*
 * Test suite hooks.
 */

/* Hook declarations. */
PicoTestSuiteEnterProc enterTestSuite;
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER enterTestSuite

/* Hook function. */
void enterTestSuite(const char *suiteName, int nb) {
    indent(level++);
    printf("running test suite %s (%d subtests)...\n", suiteName, nb);
}


/* Hook declarations. */
PicoTestSuiteLeaveProc leaveTestSuite;
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_SUITE_LEAVE leaveTestSuite

/* Hook function. */
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    indent(--level);
    printf("test suite %s done (%d failures)\n", suiteName, fail);
}


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


/*
 * Test fixture hooks.
 */

/* Hook declarations. */
PicoTestFixtureBeforeSetupProc beforeSetup;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#define PICOTEST_FIXTURE_BEFORE_SETUP beforeSetup

/* Hook function. */
void beforeSetup(const char *fixtureName, const char *testName) {
    indent(level++);
    printf("fixture %s setup...", fixtureName);
}


/* Hook declarations. */
PicoTestFixtureAfterSetupProc afterSetup;
#undef PICOTEST_FIXTURE_AFTER_SETUP
#define PICOTEST_FIXTURE_AFTER_SETUP afterSetup

/* Hook function. */
void afterSetup(const char *fixtureName, const char *testName) {
    printf(" done\n");
    --level;
}


/* Hook declarations. */
PicoTestFixtureBeforeTeardownProc beforeTeardown;
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN beforeTeardown

/* Hook function. */
void beforeTeardown(const char *fixtureName, const char *testName, int fail) {
    indent(level++);
    printf("fixture %s teardown...", fixtureName);
}


/* Hook declarations. */
PicoTestFixtureAfterTeardownProc afterTeardown;
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_AFTER_TEARDOWN afterTeardown

/* Hook function. */
void afterTeardown(const char *fixtureName, const char *testName, int fail) {
    printf(" done\n");
    --level;
}


/*
 * Test case hooks.
 */

/* Hook declarations. */
PicoTestCaseEnterProc enterTestCase;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER enterTestCase

/* Hook function. */
void enterTestCase(const char *testName) {
    indent(level++);
    printf("running test case %s...\n", testName);
}


/* Hook declarations. */
PicoTestCaseLeaveProc leaveTestCase;
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_LEAVE leaveTestCase

/* Hook function. */
void leaveTestCase(const char *testName, int fail) {
    indent(--level);
    printf("test case %s done (%d failures)\n", testName, fail);
}


/*
 * Assertion hooks.
 */

/* Hook declarations. */
PicoTestAssertBeforeProc beforeAssert;
#undef PICOTEST_ASSERT_BEFORE
#define PICOTEST_ASSERT_BEFORE beforeAssert

/* Hook function. */
void beforeAssert(const char *type, const char *test) {
    indent(level++);
    printf("before assertion %s(%s)...\n", type, test);
}


/* Hook declarations. */
PicoTestAssertAfterProc afterAssert;
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_AFTER afterAssert

/* Hook function. */
void afterAssert(const char *type, const char *test, int fail) {
    indent(--level);
    printf("after assertion %s(%s) => %s\n", type, test, fail ? "fails" : "passes");
}


/* Main test suite */
#include "mainSuite.inc"

void main() {
    mainSuite(NULL);
}
```


[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)