<a id="logger_8c"></a>
# File logger.c

![][C++]

**Location**: `examples/logger.c`

Example of PicoTest error logging, prints location and info of failed assertions to stdout.

```cpp

#include <stdio.h>
#include <picotest.h>

/* Test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test failure logger function. */
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
/* Hooks */
PicoTestCaseEnterProc logEnter;
PicoTestCaseLeaveProc logLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER logEnter
#define PICOTEST_CASE_LEAVE logLeave

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logEnter(const char *name) {
    indent(level++);
    printf("begin %s\n", name);
}
void logLeave(const char *name, int fail) {
    level--;
    if (!fail) {
        indent(level);
        printf("end %s\n", name);
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

/* Test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test failure logger function. */
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
/* Hooks */
PicoTestCaseEnterProc logEnter;
PicoTestCaseLeaveProc logLeave;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER logEnter
#define PICOTEST_CASE_LEAVE logLeave

int level = 0;
void indent(int level) {
    while (level--) printf("  ");
}
void logEnter(const char *name) {
    indent(level++);
    printf("begin %s\n", name);
}
void logLeave(const char *name, int fail) {
    level--;
    if (!fail) {
        indent(level);
        printf("end %s\n", name);
    }
}

/* Main test suite */
#include "mainSuite.inc"

void main() {
    mainSuite(NULL);
}
```

[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)