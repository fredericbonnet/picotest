<a id="main_suite_8inc"></a>
# File mainSuite.inc

![][C++]

**Location**: `examples/mainSuite.inc`

Example of a simple PicoTest suite.

Included by other examples to demonstrate how the same suite can be integrated in a variety of situations.





```cpp

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <picotest.h>

/*
 * Test suites.
 */

/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)


/*
 * Test fixtures.
 */

/* Static var initialized by fixture setup */
static int staticVar = 0;

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

/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};

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


/*
 * Test cases.
 */

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
PICOTEST_CASE(testCase3, fixtureWithContext, context) {
    PICOTEST_ASSERT(staticVar == 2);        /* Passes */
    PICOTEST_ASSERT(context->var1 == 1);    /* Passes */
    PICOTEST_VERIFY(context->var2 == NULL); /* Logs error and continue */
    PICOTEST_ASSERT(context->var3 == NULL); /* Logs error and abort */
}

/* Another test using **simpleFixture**. Tests need not belong to the same suite
 * to share a fixture. */
PICOTEST_CASE(testCase4, simpleFixture) {
    PICOTEST_VERIFY(staticVar == 1);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}

/* This test uses a fixture that requires a context. In this case the context
 * passed to the fixture setup and teardown functions is NULL. */
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}


```

## Source

```cpp

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <picotest.h>

/*
 * Test suites.
 */

/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)


/*
 * Test fixtures.
 */

/* Static var initialized by fixture setup */
static int staticVar = 0;

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

/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};

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


/*
 * Test cases.
 */

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
PICOTEST_CASE(testCase3, fixtureWithContext, context) {
    PICOTEST_ASSERT(staticVar == 2);        /* Passes */
    PICOTEST_ASSERT(context->var1 == 1);    /* Passes */
    PICOTEST_VERIFY(context->var2 == NULL); /* Logs error and continue */
    PICOTEST_ASSERT(context->var3 == NULL); /* Logs error and abort */
}

/* Another test using **simpleFixture**. Tests need not belong to the same suite
 * to share a fixture. */
PICOTEST_CASE(testCase4, simpleFixture) {
    PICOTEST_VERIFY(staticVar == 1);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}

/* This test uses a fixture that requires a context. In this case the context
 * passed to the fixture setup and teardown functions is NULL. */
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}


```

[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)