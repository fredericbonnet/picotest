<a id="fixtures_8c"></a>
# File fixtures.c

![][C++]

**Location**: `examples/fixtures.c`

Demonstrates test fixture call sequences.

```cpp

#include <stdio.h>
#include <picotest.h>

/* Hooks */
PicoTestCaseEnterProc logCaseEnter;
PicoTestCaseLeaveProc logCaseLeave;
PicoTestFixtureBeforeSetupProc logSetup;
PicoTestFixtureBeforeTeardownProc logTeardown;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_CASE_ENTER logCaseEnter
#define PICOTEST_CASE_LEAVE logCaseLeave
#define PICOTEST_FIXTURE_BEFORE_SETUP logSetup
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN logTeardown

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logCaseEnter(const char *name) {
    indent(level++);
    printf("running test case %s\n", name);
}
void logCaseLeave(const char *name, int fail) {
    indent(--level);
    if (fail) {
        printf("test case %s failed\n", name);
    } else {
        printf("test case %s completed successfully\n", name);
    }
}
void logSetup(const char *fixture, const char *test) {
    indent(level+1);
    printf("fixture setup %s before test case %s\n", fixture, test);
}
void logTeardown(const char *fixture, const char *test, int fail) {
    indent(level+1);
    if (fail) {
        printf("fixture teardown %s after failed test case %s\n", fixture, test);
    } else {
        printf("fixture teardown %s after successful test case %s\n", fixture, test);
    }
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

/* Hooks */
PicoTestCaseEnterProc logCaseEnter;
PicoTestCaseLeaveProc logCaseLeave;
PicoTestFixtureBeforeSetupProc logSetup;
PicoTestFixtureBeforeTeardownProc logTeardown;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_CASE_ENTER logCaseEnter
#define PICOTEST_CASE_LEAVE logCaseLeave
#define PICOTEST_FIXTURE_BEFORE_SETUP logSetup
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN logTeardown

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logCaseEnter(const char *name) {
    indent(level++);
    printf("running test case %s\n", name);
}
void logCaseLeave(const char *name, int fail) {
    indent(--level);
    if (fail) {
        printf("test case %s failed\n", name);
    } else {
        printf("test case %s completed successfully\n", name);
    }
}
void logSetup(const char *fixture, const char *test) {
    indent(level+1);
    printf("fixture setup %s before test case %s\n", fixture, test);
}
void logTeardown(const char *fixture, const char *test, int fail) {
    indent(level+1);
    if (fail) {
        printf("fixture teardown %s after failed test case %s\n", fixture, test);
    } else {
        printf("fixture teardown %s after successful test case %s\n", fixture, test);
    }
}

/* Main test suite */
#include "mainSuite.inc"

void main() {
    mainSuite(NULL);
}
```

[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)