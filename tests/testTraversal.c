#include <stdio.h>

#include <picotest.h>

/*
 * Test utilities
 */

#define MAX_TESTS 6
static struct {
    int nbTests;
    int nbSuites;
    int nbCases;
    int testCalled;
    struct {
        const char *name;
        int nb;
    } tests[MAX_TESTS];
} state;
void init() {
    memset(&state, 0, sizeof(state));
}
PicoTestTraverseProc traverse;
static void traverse(const char *name, int nb) {
    int i = state.nbTests++;
    if (nb) {
        state.nbSuites++;
    } else {
        state.nbCases++;
    }
    if (i < MAX_TESTS) {
        state.tests[i].name = name;
        state.tests[i].nb = nb;
    }
}

PICOTEST_SUITE(doTraverseSuite, doTraverseCase1, doTraverseSubsuite,
               doTraverseCase2);
PICOTEST_SUITE(doTraverseSubsuite, doTraverseSubcase1, doTraverseSubcase2)

PICOTEST_CASE(doTraverseCase1) {
    state.testCalled++;
}
PICOTEST_CASE(doTraverseCase2) {
    state.testCalled++;
}
PICOTEST_CASE(doTraverseSubcase1) {
    state.testCalled++;
}
PICOTEST_CASE(doTraverseSubcase2) {
    state.testCalled++;
}

/*
 * Test suite for traversal
 */
#include "hooks.h"

PICOTEST_SUITE(testTraversal, testTraverseShouldNotRunTests,
               testTraverseShouldTraverseTestsDepthFirst,
               testTraverseShouldGetTestInfo);

PICOTEST_CASE(testTraverseShouldNotRunTests) {
    init();
    PICOTEST_TRAVERSE(doTraverseSuite, traverse);
    PICOTEST_ASSERT(state.testCalled == 0);
}
PICOTEST_CASE(testTraverseShouldTraverseTestsDepthFirst) {
    init();
    PICOTEST_TRAVERSE(doTraverseSuite, traverse);
    PICOTEST_ASSERT(state.nbTests == 6);

    PICOTEST_VERIFY(strcmp(state.tests[0].name, "doTraverseSuite") == 0);
    PICOTEST_VERIFY(strcmp(state.tests[1].name, "doTraverseCase1") == 0);
    PICOTEST_VERIFY(strcmp(state.tests[2].name, "doTraverseSubsuite") == 0);
    PICOTEST_VERIFY(strcmp(state.tests[3].name, "doTraverseSubcase1") == 0);
    PICOTEST_VERIFY(strcmp(state.tests[4].name, "doTraverseSubcase2") == 0);
    PICOTEST_VERIFY(strcmp(state.tests[5].name, "doTraverseCase2") == 0);
}
PICOTEST_CASE(testTraverseShouldGetTestInfo) {
    init();
    PICOTEST_TRAVERSE(doTraverseSuite, traverse);
    PICOTEST_ASSERT(state.nbTests == 6);
    PICOTEST_VERIFY(state.nbSuites == 2);
    PICOTEST_VERIFY(state.nbCases == 4);

    PICOTEST_VERIFY(strcmp(state.tests[0].name, "doTraverseSuite") == 0);
    PICOTEST_VERIFY(state.tests[0].nb == 3);
    PICOTEST_VERIFY(strcmp(state.tests[1].name, "doTraverseCase1") == 0);
    PICOTEST_VERIFY(state.tests[1].nb == 0);
    PICOTEST_VERIFY(strcmp(state.tests[2].name, "doTraverseSubsuite") == 0);
    PICOTEST_VERIFY(state.tests[2].nb == 2);
    PICOTEST_VERIFY(strcmp(state.tests[3].name, "doTraverseSubcase1") == 0);
    PICOTEST_VERIFY(state.tests[3].nb == 0);
    PICOTEST_VERIFY(strcmp(state.tests[4].name, "doTraverseSubcase2") == 0);
    PICOTEST_VERIFY(state.tests[4].nb == 0);
    PICOTEST_VERIFY(strcmp(state.tests[5].name, "doTraverseCase2") == 0);
    PICOTEST_VERIFY(state.tests[5].nb == 0);
}