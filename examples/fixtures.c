/**
 * @file fixtures.c
 * 
 * Example of a PicoTest suite with fixtures.
 *
 * @include fixtures.c
 * @cond IGNORE 
 */
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <picotest.h>

/* Static var initialized by fixture setup */
static int staticVar = 0;

/*! [Simple fixture] */
/* Simple fixture */
PICOTEST_FIXTURE_SETUP(simpleFixture) {
    /* Initialize static stuff */
    staticVar = 1;
    srand(1234);
}
PICOTEST_FIXTURE_TEARDOWN(simpleFixture) {
    /* Cleanup static stuff */
    staticVar = 0;
    srand(clock());
}
/*! [Simple fixture] */

/*! [Fixture with context] */
/*! [PICOTEST_FIXTURE_CONTEXT example] */
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};
/*! [PICOTEST_FIXTURE_CONTEXT example] */

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithContext, context) {
    /* Initialize static stuff */
    staticVar = 2;

    /* Initialize fixture context */
    context->var1 = 1;
    context->var2 = "test";
    context->var3 = (void *) malloc(1);
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    free(context->var3);
}
/*! [Fixture with context] */

/*! [Fixture with optional context] */
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithOptionalContext) {
    void *buffer;
};

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithOptionalContext, context) {
    /* Initialize static stuff */
    staticVar = 3;

    /* Initialize fixture context */
    if (context) {
        staticVar++;
        context->buffer = (void *) malloc(1);
    }
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithOptionalContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    if (context) {
        free(context->buffer);
    }
}
/*! [Fixture with optional context] */


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
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)

/* Tests */
/*! [PICOTEST_CASE with fixtures] */
#define FAILS 0
#define PASSES 1

/* Simple test with no fixture */
PICOTEST_CASE(testCase1) {
    PICOTEST_VERIFY(FAILS); /* Logs error and continue */
    PICOTEST_ASSERT(FAILS); /* Logs error and abort */
    /* Unreached */
    PICOTEST_ASSERT(PASSES);
}

/* Test with fixture but no context */
PICOTEST_CASE(testCase2, simpleFixture) {
    PICOTEST_ASSERT(staticVar == 1);    /* Passes */
    PICOTEST_VERIFY(FAILS);             /* Logs error and continue */
}

/* Test with fixture and context. Tests belonging to the same suite don't have
 * to share the same suite. */
/*! [PICOTEST_CASE with fixture and context] */
PICOTEST_CASE(testCase3, fixtureWithContext, context) {
    PICOTEST_ASSERT(staticVar == 2);        /* Passes */
    PICOTEST_ASSERT(context->var1 == 1);    /* Passes */
    PICOTEST_VERIFY(context->var2 == NULL); /* Logs error and continue */
    PICOTEST_ASSERT(context->var3 == NULL); /* Logs error and abort */
}
/*! [PICOTEST_CASE with fixture and context] */

/* Another test using **simpleFixture**. Tests need not belong to the same suite
 *  to share a fixture. */
PICOTEST_CASE(testCase4, simpleFixture) {
    PICOTEST_VERIFY(staticVar == 1);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}

/* This test uses a fixture that requires a context. In this case the context
 * passed to the fixture setup and teardown functions is NULL. */
/*! [PICOTEST_CASE with fixture and optional context] */
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}
/*! [PICOTEST_CASE with fixture and optional context] */
/*! [PICOTEST_CASE with fixtures] */

void main() {
    mainSuite(NULL);
}
/** @endcond */
