<a id="tags_8c"></a>
# File tags.c

![][C++]

**Location**: `examples/tags.c`

Advanced example of PicoTest test filter, implements a primitive tagging feature for test filtering.

```cpp

#include <stdio.h>
#include <picotest.h>

/* Custom test filter function declaration. */
PicoTestFilterProc matchTag;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchTag

/* Tags for test filtering */
typedef struct TestTags {
    PicoTestProc *test;
    const char *tags[10];
} TestTags;
TestTags taggedTests[];

/*
 * Test filter function. **cond** is a tag name, optionally prefixed by '!' for
 * negation.
 * 
 * Positive tagging, e.g. "tagname":
 * - Test suites tagged "tagname" will run with all their subtests
 *   (PICOTEST_FILTER_PASS).
 * - Test suites not tagged "tagname" won't run but will propagate the filter to
 *   their subtests (PICOTEST_FILTER_SKIP_PROPAGATE).
 * 
 * Negative tagging, e.g. "!tagname":
 * - Test suites tagged "tagname" won't run but will propagate the filter
 *   to their subtests (PICOTEST_FILTER_SKIP_PROPAGATE).
 * - Test suites not tagged "tagname" will run and will propagate the filter to
 *   their subtests (PICOTEST_FILTER_PASS_PROPAGATE).
 */
PicoTestFilterResult matchTag(PicoTestProc *test, const char *testName, const char *cond) {
    TestTags *taggedTest;
    const char **tag;
    int negate = (cond[0] == '!');
    if (negate) cond++;

    /* First find test in tagged tests. */
    for (taggedTest = taggedTests; taggedTest->test; taggedTest++) {
        if (taggedTest->test != test) continue;

        /* Then find **cond** in tag list. */
        for (tag = taggedTest->tags; *tag; tag++) {
            if (strcmp(*tag, cond) == 0) {
                /* Found. */
                return (negate ? PICOTEST_FILTER_SKIP_PROPAGATE : PICOTEST_FILTER_PASS);
            }
        }
        break;
    }

    /* Not found. */
    return (negate ? PICOTEST_FILTER_PASS_PROPAGATE : PICOTEST_FILTER_SKIP_PROPAGATE);
}

/* Hooks */
PicoTestCaseEnterProc logCaseEnter;
PicoTestCaseLeaveProc logCaseLeave;
PicoTestSuiteEnterProc logSuiteEnter;
PicoTestSuiteLeaveProc logSuiteLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_CASE_ENTER logCaseEnter
#define PICOTEST_CASE_LEAVE logCaseLeave
#define PICOTEST_SUITE_ENTER logSuiteEnter
#define PICOTEST_SUITE_LEAVE logSuiteLeave

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logCaseEnter(const char *name) {
    indent(level++);
    printf("running test case %s\n", name);
}
void logCaseLeave(const char *name, int fail) {
    level--;
}
void logSuiteEnter(const char *name, int nb) {
    indent(level++);
    printf("running test suite %s\n", name);
}
void logSuiteLeave(const char *name, int nb, int fail) {
    level--;
}

/* Main test suite */
#include "mainSuite.inc"

/* Tagged tests */
TestTags taggedTests[] = {
    {testCase1, {"tag1", "tag4", NULL}},
    {testCase2, {"tag2", NULL}},
    {subSuite,  {"tag3", NULL}},
    {testCase4, {"tag4", NULL}},
    {NULL}
};

void main() {
    /*
     * Run all tests in order:
     * 
     * running test suite mainSuite
     *   running test case testCase1
     *   running test case testCase2
     *   running test suite subSuite
     *     running test case testCase4
     *     running test case testCase5
     *   running test case testCase3
     */
    printf("Run all tests:\n");
    mainSuite(NULL);
    printf("\n");

    /*
     * Run tests tagged "tag3":
     * 
     * running test suite subSuite
     *   running test case testCase4
     *   running test case testCase5
     */
    printf("Run tests tagged \"tag3\":\n");
    mainSuite("tag3");
    printf("\n");

    /*
     * Run tests not tagged "tag4":
     * running test suite mainSuite
     *   running test case testCase2
     *   running test suite subSuite
     *     running test case testCase5
     *   running test case testCase3
     */
    printf("Run tests not tagged \"tag4\":\n");
    mainSuite("!tag4");
    printf("\n");
}
```

## Source

```cpp

#include <stdio.h>
#include <picotest.h>

/* Custom test filter function declaration. */
PicoTestFilterProc matchTag;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchTag

/* Tags for test filtering */
typedef struct TestTags {
    PicoTestProc *test;
    const char *tags[10];
} TestTags;
TestTags taggedTests[];

/*
 * Test filter function. **cond** is a tag name, optionally prefixed by '!' for
 * negation.
 * 
 * Positive tagging, e.g. "tagname":
 * - Test suites tagged "tagname" will run with all their subtests
 *   (PICOTEST_FILTER_PASS).
 * - Test suites not tagged "tagname" won't run but will propagate the filter to
 *   their subtests (PICOTEST_FILTER_SKIP_PROPAGATE).
 * 
 * Negative tagging, e.g. "!tagname":
 * - Test suites tagged "tagname" won't run but will propagate the filter
 *   to their subtests (PICOTEST_FILTER_SKIP_PROPAGATE).
 * - Test suites not tagged "tagname" will run and will propagate the filter to
 *   their subtests (PICOTEST_FILTER_PASS_PROPAGATE).
 */
PicoTestFilterResult matchTag(PicoTestProc *test, const char *testName, const char *cond) {
    TestTags *taggedTest;
    const char **tag;
    int negate = (cond[0] == '!');
    if (negate) cond++;

    /* First find test in tagged tests. */
    for (taggedTest = taggedTests; taggedTest->test; taggedTest++) {
        if (taggedTest->test != test) continue;

        /* Then find **cond** in tag list. */
        for (tag = taggedTest->tags; *tag; tag++) {
            if (strcmp(*tag, cond) == 0) {
                /* Found. */
                return (negate ? PICOTEST_FILTER_SKIP_PROPAGATE : PICOTEST_FILTER_PASS);
            }
        }
        break;
    }

    /* Not found. */
    return (negate ? PICOTEST_FILTER_PASS_PROPAGATE : PICOTEST_FILTER_SKIP_PROPAGATE);
}

/* Hooks */
PicoTestCaseEnterProc logCaseEnter;
PicoTestCaseLeaveProc logCaseLeave;
PicoTestSuiteEnterProc logSuiteEnter;
PicoTestSuiteLeaveProc logSuiteLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_CASE_ENTER logCaseEnter
#define PICOTEST_CASE_LEAVE logCaseLeave
#define PICOTEST_SUITE_ENTER logSuiteEnter
#define PICOTEST_SUITE_LEAVE logSuiteLeave

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logCaseEnter(const char *name) {
    indent(level++);
    printf("running test case %s\n", name);
}
void logCaseLeave(const char *name, int fail) {
    level--;
}
void logSuiteEnter(const char *name, int nb) {
    indent(level++);
    printf("running test suite %s\n", name);
}
void logSuiteLeave(const char *name, int nb, int fail) {
    level--;
}

/* Main test suite */
#include "mainSuite.inc"

/* Tagged tests */
TestTags taggedTests[] = {
    {testCase1, {"tag1", "tag4", NULL}},
    {testCase2, {"tag2", NULL}},
    {subSuite,  {"tag3", NULL}},
    {testCase4, {"tag4", NULL}},
    {NULL}
};

void main() {
    /*
     * Run all tests in order:
     * 
     * running test suite mainSuite
     *   running test case testCase1
     *   running test case testCase2
     *   running test suite subSuite
     *     running test case testCase4
     *     running test case testCase5
     *   running test case testCase3
     */
    printf("Run all tests:\n");
    mainSuite(NULL);
    printf("\n");

    /*
     * Run tests tagged "tag3":
     * 
     * running test suite subSuite
     *   running test case testCase4
     *   running test case testCase5
     */
    printf("Run tests tagged \"tag3\":\n");
    mainSuite("tag3");
    printf("\n");

    /*
     * Run tests not tagged "tag4":
     * running test suite mainSuite
     *   running test case testCase2
     *   running test suite subSuite
     *     running test case testCase5
     *   running test case testCase3
     */
    printf("Run tests not tagged \"tag4\":\n");
    mainSuite("!tag4");
    printf("\n");
}
```

[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)