#include <picotest.h>

/*
 * Test utilities
 */

static struct {
    int testCaseStep;
    struct {
        int step;
        const char *fixtureName;
        const char *testName;
    } testFixtureBeforeSetup;
    struct {
        int step;
        const char *fixtureName;
        const char *testName;
    } testFixtureAfterSetup;
    struct {
        int step;
        const char *fixtureName;
        const char *testName;
        int fail;
    } testFixtureBeforeTeardown;
    struct {
        int step;
        const char *fixtureName;
        const char *testName;
        int fail;
    } testFixtureAfterTeardown;
} state;
static void init() {
    memset(&state, 0, sizeof(state));
}

/* Hooks used for testing */
static PicoTestFixtureBeforeSetupProc testFixtureBeforeSetup;
static PicoTestFixtureAfterSetupProc testFixtureAfterSetup;
static PicoTestFixtureBeforeTeardownProc testFixtureBeforeTeardown;
static PicoTestFixtureAfterTeardownProc testFixtureAfterTeardown;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#undef PICOTEST_FIXTURE_AFTER_SETUP
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_SETUP testFixtureBeforeSetup
#define PICOTEST_FIXTURE_AFTER_SETUP testFixtureAfterSetup
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN testFixtureBeforeTeardown
#define PICOTEST_FIXTURE_AFTER_TEARDOWN testFixtureAfterTeardown
void testFixtureBeforeSetup(const char *fixtureName, const char *testName) {
    state.testFixtureBeforeSetup.step = ++state.testCaseStep;
    state.testFixtureBeforeSetup.fixtureName = fixtureName;
    state.testFixtureBeforeSetup.testName = testName;
}
void testFixtureAfterSetup(const char *fixtureName, const char *testName) {
    state.testFixtureAfterSetup.step = ++state.testCaseStep;
    state.testFixtureAfterSetup.fixtureName = fixtureName;
    state.testFixtureAfterSetup.testName = testName;
}
void testFixtureBeforeTeardown(const char *fixtureName, const char *testName,
                               int fail) {
    state.testFixtureBeforeTeardown.step = ++state.testCaseStep;
    state.testFixtureBeforeTeardown.fixtureName = fixtureName;
    state.testFixtureBeforeTeardown.testName = testName;
    state.testFixtureBeforeTeardown.fail = fail;
}
void testFixtureAfterTeardown(const char *fixtureName, const char *testName,
                              int fail) {
    state.testFixtureAfterTeardown.step = ++state.testCaseStep;
    state.testFixtureAfterTeardown.fixtureName = fixtureName;
    state.testFixtureAfterTeardown.testName = testName;
    state.testFixtureAfterTeardown.fail = fail;
}

PICOTEST_CASE(doPassNoFixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFailNoFixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(0);
    state.testCaseStep++;
}
PICOTEST_FIXTURE_SETUP(fixture) {}
PICOTEST_FIXTURE_TEARDOWN(fixture) {}
PICOTEST_CASE(doPassFixture, fixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(1);
    state.testCaseStep++;
}
PICOTEST_CASE(doFailFixture, fixture) {
    state.testCaseStep++;
    PICOTEST_ASSERT(0);
    state.testCaseStep++;
}

/* Reset default settings */
#include "reset.h"

/*
 * Test suite for test fixture hooks
 */
#include "hooks.h"

PICOTEST_SUITE(testFixtureHooks, testFixtureHooksNoFixture,
               testFixtureHooksCallOrder, testFixtureBeforeSetupHook,
               testFixtureAfterSetupHook, testFixtureBeforeTeardownHook,
               testFixtureAfterTeardownHook);

PICOTEST_SUITE(testFixtureHooksNoFixture, testFixtureHooksNoFixturePass,
               testFixtureHooksNoFixtureFail)
PICOTEST_CASE(testFixtureHooksNoFixturePass) {
    init();
    doPassNoFixture(NULL);
    PICOTEST_VERIFY(state.testFixtureBeforeSetup.step == 0);
    PICOTEST_VERIFY(state.testFixtureAfterSetup.step == 0);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.step == 0);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.step == 0);
}
PICOTEST_CASE(testFixtureHooksNoFixtureFail) {
    init();
    doFailNoFixture(NULL);
    PICOTEST_VERIFY(state.testFixtureBeforeSetup.step == 0);
    PICOTEST_VERIFY(state.testFixtureAfterSetup.step == 0);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.step == 0);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.step == 0);
}

PICOTEST_SUITE(testFixtureHooksCallOrder, testFixtureHooksCallOrderPass,
               testFixtureHooksCallOrderFail)
PICOTEST_CASE(testFixtureHooksCallOrderPass) {
    init();
    doPassFixture(NULL);
    PICOTEST_VERIFY(state.testFixtureBeforeSetup.step == 1);
    PICOTEST_VERIFY(state.testFixtureAfterSetup.step == 2);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.step == 5);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.step == 6);
}
PICOTEST_CASE(testFixtureHooksCallOrderFail) {
    init();
    doFailFixture(NULL);
    PICOTEST_VERIFY(state.testFixtureBeforeSetup.step == 1);
    PICOTEST_VERIFY(state.testFixtureAfterSetup.step == 2);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.step == 4);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.step == 5);
}

/*
 * PICOTEST_FIXTURE_BEFORE_SETUP
 */

PICOTEST_SUITE(testFixtureBeforeSetupHook, testFixtureBeforeSetupHookPass,
               testFixtureBeforeSetupHookFail);
PICOTEST_CASE(testFixtureBeforeSetupHookPass) {
    init();
    doPassFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeSetup.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeSetup.testName, "doPassFixture") == 0);
}
PICOTEST_CASE(testFixtureBeforeSetupHookFail) {
    init();
    doFailFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeSetup.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeSetup.testName, "doFailFixture") == 0);
}

/*
 * PICOTEST_FIXTURE_AFTER_SETUP
 */

PICOTEST_SUITE(testFixtureAfterSetupHook, testFixtureAfterSetupHookPass,
               testFixtureAfterSetupHookFail);
PICOTEST_CASE(testFixtureAfterSetupHookPass) {
    init();
    doPassFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterSetup.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterSetup.testName, "doPassFixture") == 0);
}
PICOTEST_CASE(testFixtureAfterSetupHookFail) {
    init();
    doFailFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterSetup.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterSetup.testName, "doFailFixture") == 0);
}

/*
 * PICOTEST_FIXTURE_BEFORE_TEARDOWN
 */

PICOTEST_SUITE(testFixtureBeforeTeardownHook, testFixtureBeforeTeardownHookPass,
               testFixtureBeforeTeardownHookFail);
PICOTEST_CASE(testFixtureBeforeTeardownHookPass) {
    init();
    doPassFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeTeardown.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeTeardown.testName, "doPassFixture") == 0);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.fail == 0);
}
PICOTEST_CASE(testFixtureBeforeTeardownHookFail) {
    init();
    doFailFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeTeardown.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureBeforeTeardown.testName, "doFailFixture") == 0);
    PICOTEST_VERIFY(state.testFixtureBeforeTeardown.fail == 1);
}

/*
 * PICOTEST_FIXTURE_AFTER_TEARDOWN
 */

PICOTEST_SUITE(testFixtureAfterTeardownHook, testFixtureAfterTeardownHookPass,
               testFixtureAfterTeardownHookFail);
PICOTEST_CASE(testFixtureAfterTeardownHookPass) {
    init();
    doPassFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterTeardown.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterTeardown.testName, "doPassFixture") == 0);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.fail == 0);
}
PICOTEST_CASE(testFixtureAfterTeardownHookFail) {
    init();
    doFailFixture(NULL);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterTeardown.fixtureName, "fixture") == 0);
    PICOTEST_VERIFY(
        strcmp(state.testFixtureAfterTeardown.testName, "doFailFixture") == 0);
    PICOTEST_VERIFY(state.testFixtureAfterTeardown.fail == 1);
}
