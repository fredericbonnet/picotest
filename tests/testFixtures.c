#include <picotest.h>

/*
 * Test utilities
 */

static struct {
    int testCaseStep;
    int testFixtureSetupCalled;
    int testFixtureTeardownCalled;
    void *testFixtureSetupContext;
    void *testFixtureCaseContext;
    void *testFixtureTeardownContext;
    int testFixtureSetupContextValue;
    int testFixtureCaseContextValue;
    int testFixtureTeardownContextValue;
} state;
static void init() {
    memset(&state, 0, sizeof(state));
}

PICOTEST_FIXTURE_SETUP(fixture) {
    state.testFixtureSetupCalled = ++state.testCaseStep;
}
PICOTEST_FIXTURE_TEARDOWN(fixture) {
    state.testFixtureTeardownCalled = ++state.testCaseStep;
}
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int contextValue;
};
PICOTEST_FIXTURE_SETUP(fixtureWithContext, context) {
    state.testFixtureSetupCalled = ++state.testCaseStep;
    state.testFixtureSetupContext = context;
    if (context) {
        context->contextValue = state.testCaseStep;
        state.testFixtureSetupContextValue = context->contextValue;
    }
}
PICOTEST_FIXTURE_TEARDOWN(fixtureWithContext, context) {
    state.testFixtureTeardownCalled = ++state.testCaseStep;
    state.testFixtureTeardownContext = context;
    if (context) {
        context->contextValue = state.testCaseStep;
        state.testFixtureTeardownContextValue = context->contextValue;
    }
}

PICOTEST_CASE(doNoFixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixturePass, fixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixtureFail, fixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(0);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixtureWithContextPass, fixtureWithContext, context) {
    context->contextValue = ++state.testCaseStep;
    state.testFixtureCaseContext = context;
    state.testFixtureCaseContextValue = context->contextValue;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixtureWithContextFail, fixtureWithContext, context) {
    context->contextValue = ++state.testCaseStep;
    state.testFixtureCaseContext = context;
    state.testFixtureCaseContextValue = context->contextValue;
    PICOTEST_ASSERT(0);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixtureWithOptionalContextPass, fixtureWithContext) {
    state.testCaseStep++;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFixtureWithOptionalContextFail, fixtureWithContext) {
    state.testCaseStep++;
    PICOTEST_ASSERT(0);
    state.testCaseStep++;
}

/*
 * Test suite for test fixtures
 */
#include "hooks.h"

PICOTEST_SUITE(testFixtures, testFixtureShouldBeOptional, testFixtureSetup,
               testFixtureTeardown, testFixtureSetupContext);

PICOTEST_CASE(testFixtureShouldBeOptional) {
    init();
    doNoFixture(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 0);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 0);
}

/*
 * PICOTEST_FIXTURE_SETUP
 */

PICOTEST_SUITE(testFixtureSetup, testFixtureSetupShouldRunBeforeTest,
               testFixtureSetupShouldGetContext);

PICOTEST_CASE(testFixtureSetupShouldRunBeforeTest) {
    init();
    doFixturePass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);

    init();
    doFixtureFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);

    init();
    doFixtureWithContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);

    init();
    doFixtureWithContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);

    init();
    doFixtureWithOptionalContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);

    init();
    doFixtureWithOptionalContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupCalled == 1);
}
PICOTEST_CASE(testFixtureSetupShouldGetContext) {
    init();
    doFixturePass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);

    init();
    doFixtureFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);

    init();
    doFixtureWithContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext != NULL);

    init();
    doFixtureWithContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext != NULL);

    init();
    doFixtureWithOptionalContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);

    init();
    doFixtureWithOptionalContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);
}

/*
 * PICOTEST_FIXTURE_TEARDOWN
 */

PICOTEST_SUITE(testFixtureTeardown, testFixtureTeardownShouldRunAfterTest,
               testFixtureTeardownShouldGetContext);

PICOTEST_CASE(testFixtureTeardownShouldRunAfterTest) {
    init();
    doFixturePass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 4);

    init();
    doFixtureFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 3);

    init();
    doFixtureWithContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 4);

    init();
    doFixtureWithContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 3);

    init();
    doFixtureWithOptionalContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 4);

    init();
    doFixtureWithOptionalContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownCalled == 3);
}
PICOTEST_CASE(testFixtureTeardownShouldGetContext) {
    init();
    doFixturePass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);

    init();
    doFixtureFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);

    init();
    doFixtureWithContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext != NULL);

    init();
    doFixtureWithContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext != NULL);

    init();
    doFixtureWithOptionalContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);

    init();
    doFixtureWithOptionalContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);
}

/*
 * PICOTEST_FIXTURE_CONTEXT
 */

PICOTEST_SUITE(testFixtureSetupContext, testFixtureSetupContextShouldBeOptional,
               testFixtureSetupContextShouldFollowTestRun);

PICOTEST_CASE(testFixtureSetupContextShouldBeOptional) {
    init();
    doFixtureWithOptionalContextPass(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);
    PICOTEST_VERIFY(state.testFixtureCaseContext == NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);

    init();
    doFixtureWithOptionalContextFail(NULL);
    PICOTEST_VERIFY(state.testFixtureSetupContext == NULL);
    PICOTEST_VERIFY(state.testFixtureCaseContext == NULL);
    PICOTEST_VERIFY(state.testFixtureTeardownContext == NULL);
}
PICOTEST_CASE(testFixtureSetupContextShouldFollowTestRun) {
    init();
    doFixtureWithContextPass(NULL);
    PICOTEST_ASSERT(state.testFixtureSetupContext != NULL);
    PICOTEST_VERIFY(state.testFixtureCaseContext ==
                    state.testFixtureSetupContext);
    PICOTEST_VERIFY(state.testFixtureTeardownContext ==
                    state.testFixtureSetupContext);
    PICOTEST_VERIFY(state.testFixtureSetupContextValue == 1);
    PICOTEST_VERIFY(state.testFixtureCaseContextValue == 2);
    PICOTEST_VERIFY(state.testFixtureTeardownContextValue == 4);

    init();
    doFixtureWithContextFail(NULL);
    PICOTEST_ASSERT(state.testFixtureSetupContext != NULL);
    PICOTEST_VERIFY(state.testFixtureCaseContext ==
                    state.testFixtureSetupContext);
    PICOTEST_VERIFY(state.testFixtureTeardownContext ==
                    state.testFixtureSetupContext);
    PICOTEST_VERIFY(state.testFixtureSetupContextValue == 1);
    PICOTEST_VERIFY(state.testFixtureCaseContextValue == 2);
    PICOTEST_VERIFY(state.testFixtureTeardownContextValue == 3);
}