/**
 * @file picotestRunner.inc
 *
 * This file provides a fully functional test runner and hooks for picotest
 * suites. It's the easiest way to add PicoTest support to a new or existing
 * project with minimal effort. See PicoTest's own test suite for an example of
 * how to do it.
 *
 * @par Getting started
 *
 * - Include this file in all files that define test cases and suites. It is
 *   idempotent and can be safely included more than once.
 * - Define #PICOTEST_MAINSUITE in the main file
 *
 * That's it!
 *
 * @par Usage
 *
 * The generated executable expects the following command line arguments:
 *
 * ```sh
 * <test_runner> ?option? ?test names?
 * ```
 *
 * If the leading argument starts with `-`, it is interpreted as an option; the
 * remaining arguments provide the test names to execute.
 *
 * @par Options
 *
 * Options are mutually exclusive.
 *
 * Test lists:
 * - `-l`, `--list`: Lists all test cases (names only)
 * - `-a`, `--list-all`: Lists all test cases and suites (names only)
 * - `-h`, `--hierarchy`: Lists all test cases (`/`-separated paths)
 * - `-j`, `--list-json`: Lists all test cases and suites in JSON format (names,
 *   file paths, line numbers, subtests)
 *
 * Test output:
 * - `-J`, `--json`: Outputs a newline-delimited JSON event stream instead of
 *   plain text.
 *
 * @par License
 *
 * This file is public domain.
 *
 * Copyright (c) 2025 Frederic Bonnet
 */
#include <picotest.h>

/**
 * Defining #PICOTEST_MAINSUITE before including `picotestRunner.inc` will
 * define the `main()` function with standard option parsing and run the
 * provided test suite. Only do it once per executable.
 *
 * @par Example
 *      The PicoTest test suite is a good example of how to use this macro from
 *      the main entry point:
 *
 *      @include tests/main.c
 */
#ifdef DOXYGEN
#define PICOTEST_MAINSUITE
#endif

/*! \cond IGNORE */
/* Test failure log handler */
extern PicoTestFailureLoggerProc *logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test suite tracing hooks */
extern PicoTestSuiteEnterProc *enterTestSuite;
extern PicoTestSuiteLeaveProc *leaveTestSuite;
extern PicoTestSuiteBeforeSubtestProc *beforeSubtest;
extern PicoTestSuiteAfterSubtestProc *afterSubtest;
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_ENTER enterTestSuite
#define PICOTEST_SUITE_LEAVE leaveTestSuite
#define PICOTEST_SUITE_BEFORE_SUBTEST beforeSubtest
#define PICOTEST_SUITE_AFTER_SUBTEST afterSubtest

/* Test case tracing hooks */
extern PicoTestCaseEnterProc *enterTestCase;
extern PicoTestCaseLeaveProc *leaveTestCase;
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER enterTestCase
#define PICOTEST_CASE_LEAVE leaveTestCase

#if defined(PICOTEST_MAINSUITE) && !defined(_PICOTEST_MAINSUITE)
#define _PICOTEST_MAINSUITE

#include <stdio.h>

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

static void initHooks(int json) {
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

/* Print string in JSON format */
static void printJsonString(const char *s) {
    putc('"', stdout);
    for (const char *c = s; *c; c++) {
        switch (*c) {
        case '\"':
            fputs("\\\"", stdout);
            break;
        case '\\':
            fputs("\\\\", stdout);
            break;
        case '\b':
            fputs("\\b", stdout);
            break;
        case '\f':
            fputs("\\f", stdout);
            break;
        case '\n':
            fputs("\\n", stdout);
            break;
        case '\r':
            fputs("\\r", stdout);
            break;
        case '\t':
            fputs("\\t", stdout);
            break;
        default:
            putc(*c, stdout);
        }
    }
    putc('"', stdout);
}
static void printJsonIntMember(const char *key, int value) {
    printJsonString(key);
    printf(":%d", value);
}
static void printJsonStringMember(const char *key, const char *value) {
    printJsonString(key);
    printf(":");
    printJsonString(value);
}

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

/*
 * Traversal functions
 */

/* Traversal function, will print test cases only */
static void printTestCase(const char *name, int nb) {
    if (nb == 0)
        printf("%s\n", name);
}

/* Traversal function, will print all tests */
static void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}

/* Visit function, will print test hierarchy */
static void printTestHierarchy(const PicoTestMetadata *metadata,
                               PicoTestVisitStep step) {
    static int level = 0;
    static const char *parents[20];
    int i;

    if (step == PICOTEST_VISIT_LEAVE) {
        if (metadata->nbSubtests) {
            level--;
        }
        return;
    }

    if (metadata->nbSubtests) {
        parents[level++] = metadata->name;
    } else {
        for (i = 0; i < level; i++) {
            printf("%s/", parents[i]);
        }
        printf("%s\n", metadata->name);
    }
}

/* Visit function, will print suite in JSON format */
static void printTestSuiteJson(const PicoTestMetadata *metadata,
                               PicoTestVisitStep step) {
    static int level = 0;
    static int first = 1;
    int i;

    if (step == PICOTEST_VISIT_LEAVE) {
        if (metadata->nbSubtests) {
            level--;
            printf("\n");
            for (i = 0; i < level; i++) {
                printf(" ");
            }
            printf("]");
        }
        printf("}");
        return;
    }

    if (!first) {
        printf(",\n");
    }
    first = 0;
    for (i = 0; i < level; i++) {
        printf(" ");
    }
    printf("{");

    printJsonString("name");
    printf(":");
    printJsonString(metadata->name);

    printf(",");

    printJsonString("file");
    printf(":");
    printJsonString(metadata->file);

    printf(",");
    printJsonString("line");
    printf(":%d", metadata->line);

    if (metadata->nbSubtests) {
        printf(",");

        level++;
        first = 1;
        printJsonString("subtests");
        printf(":[\n");
    }
}

/*
 * Main entry point
 */

PICOTEST_EXTERN(PICOTEST_MAINSUITE);

int main(int argc, char *argv[]) {
    int json = 0;
    int fail = 0;

    if (argc > 1 && argv[1][0] == '-') {
        if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
            /* List test cases. */
            PICOTEST_TRAVERSE(PICOTEST_MAINSUITE, printTestCase);
            return 0;
        } else if (strcmp(argv[1], "-a") == 0 ||
                   strcmp(argv[1], "--list-all") == 0) {
            /* List all tests. */
            PICOTEST_TRAVERSE(PICOTEST_MAINSUITE, printTestName);
            return 0;
        } else if (strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--hierarchy") == 0) {
            /* List all tests. */
            PICOTEST_VISIT(PICOTEST_MAINSUITE, printTestHierarchy);
            return 0;
        } else if (strcmp(argv[1], "-j") == 0 ||
                   strcmp(argv[1], "--list-json") == 0) {
            /* Print test suite as JSON. */
            PICOTEST_VISIT(PICOTEST_MAINSUITE, printTestSuiteJson);
            return 0;
        }

        if (strcmp(argv[1], "-J") == 0 || strcmp(argv[1], "--json") == 0) {
            /* Use JSON hooks. */
            json = 1;
            argc--;
            argv++;
        }
    }

    initHooks(json);

    if (argc <= 1) {
        /* Execute all tests. */
        fail = PICOTEST_MAINSUITE(NULL);
    } else {
        /* Only execute tests given as command line arguments. */
        int i;
        for (i = 1; i < argc; i++) {
            char *name = argv[i];
            char *lastSlash = strrchr(name, '/');
            if (lastSlash != NULL) {
                name = lastSlash + 1;
            }
            fail += PICOTEST_MAINSUITE(name);
        }
    }

    return fail;
}
#endif /* defined(PICOTEST_MAINSUITE) && !defined(_PICOTEST_MAINSUITE) */
/*! \endcond */
