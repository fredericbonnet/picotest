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
    int nbVisits;
    struct {
        const PicoTestMetadata *metadata;
        PicoTestVisitStep step;
    } visits[MAX_TESTS * 2];
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
PicoTestVisitProc visit;
static void visit(const PicoTestMetadata *metadata, PicoTestVisitStep step) {
    int i = state.nbVisits++;
    if (step == PICOTEST_VISIT_ENTER) {
        state.nbTests++;
        if (metadata->nbSubtests) {
            state.nbSuites++;
        } else {
            state.nbCases++;
        }
    }
    if (i < MAX_TESTS * 2) {
        state.visits[i].metadata = metadata;
        state.visits[i].step = step;
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

PICOTEST_SUITE(testTraversal, testTraverse, testVisit);

/*
 * PICOTEST_TRAVERSE
 */

PICOTEST_SUITE(testTraverse, testTraverseShouldNotRunTests,
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
    {
        PICOTEST_VERIFY(strcmp(state.tests[1].name, "doTraverseCase1") == 0);
        PICOTEST_VERIFY(strcmp(state.tests[2].name, "doTraverseSubsuite") == 0);
        {
            PICOTEST_VERIFY(strcmp(state.tests[3].name, "doTraverseSubcase1") ==
                            0);
            PICOTEST_VERIFY(strcmp(state.tests[4].name, "doTraverseSubcase2") ==
                            0);
        }
        PICOTEST_VERIFY(strcmp(state.tests[5].name, "doTraverseCase2") == 0);
    }
}
PICOTEST_CASE(testTraverseShouldGetTestInfo) {
    init();
    PICOTEST_TRAVERSE(doTraverseSuite, traverse);
    PICOTEST_ASSERT(state.nbTests == 6);
    PICOTEST_VERIFY(state.nbSuites == 2);
    PICOTEST_VERIFY(state.nbCases == 4);

    PICOTEST_VERIFY(strcmp(state.tests[0].name, "doTraverseSuite") == 0);
    PICOTEST_VERIFY(state.tests[0].nb == 3);
    {
        PICOTEST_VERIFY(strcmp(state.tests[1].name, "doTraverseCase1") == 0);
        PICOTEST_VERIFY(state.tests[1].nb == 0);

        PICOTEST_VERIFY(strcmp(state.tests[2].name, "doTraverseSubsuite") == 0);
        PICOTEST_VERIFY(state.tests[2].nb == 2);
        {
            PICOTEST_VERIFY(strcmp(state.tests[3].name, "doTraverseSubcase1") ==
                            0);
            PICOTEST_VERIFY(state.tests[3].nb == 0);

            PICOTEST_VERIFY(strcmp(state.tests[4].name, "doTraverseSubcase2") ==
                            0);
            PICOTEST_VERIFY(state.tests[4].nb == 0);
        }
        PICOTEST_VERIFY(strcmp(state.tests[5].name, "doTraverseCase2") == 0);
        PICOTEST_VERIFY(state.tests[5].nb == 0);
    }
}

/*
 * PICOTEST_VISIT
 */

PICOTEST_SUITE(testVisit, testVisitShouldNotRunTests,
               testVisitShouldVisitTestsOncePerstep,
               testVisitShouldVisitTestsDepthFirst,
               testVisitShouldGetTestMetadata);

PICOTEST_CASE(testVisitShouldNotRunTests) {
    init();
    PICOTEST_VISIT(doTraverseSuite, visit);
    PICOTEST_ASSERT(state.testCalled == 0);
}
PICOTEST_CASE(testVisitShouldVisitTestsOncePerstep) {
    init();
    PICOTEST_VISIT(doTraverseSuite, visit);
    PICOTEST_ASSERT(state.nbTests == 6, "%d %d", state.nbTests, state.nbVisits);
    PICOTEST_ASSERT(state.nbVisits == 12);
}
PICOTEST_CASE(testVisitShouldVisitTestsDepthFirst) {
    init();
    PICOTEST_VISIT(doTraverseSuite, visit);
    PICOTEST_ASSERT(state.nbVisits == 12);

    PICOTEST_VERIFY(state.visits[0].step == PICOTEST_VISIT_ENTER);
    {
        PICOTEST_VERIFY(state.visits[1].step == PICOTEST_VISIT_ENTER);
        PICOTEST_VERIFY(state.visits[2].step == PICOTEST_VISIT_LEAVE);

        PICOTEST_VERIFY(state.visits[3].step == PICOTEST_VISIT_ENTER);
        {
            PICOTEST_VERIFY(state.visits[4].step == PICOTEST_VISIT_ENTER);
            PICOTEST_VERIFY(state.visits[5].step == PICOTEST_VISIT_LEAVE);

            PICOTEST_VERIFY(state.visits[6].step == PICOTEST_VISIT_ENTER);
            PICOTEST_VERIFY(state.visits[7].step == PICOTEST_VISIT_LEAVE);
        }
        PICOTEST_VERIFY(state.visits[8].step == PICOTEST_VISIT_LEAVE);

        PICOTEST_VERIFY(state.visits[9].step == PICOTEST_VISIT_ENTER);
        PICOTEST_VERIFY(state.visits[10].step == PICOTEST_VISIT_LEAVE);
    }
    PICOTEST_VERIFY(state.visits[11].step == PICOTEST_VISIT_LEAVE);
}
PICOTEST_CASE(testVisitShouldGetTestMetadata) {
    init();
    PICOTEST_VISIT(doTraverseSuite, visit);
    PICOTEST_ASSERT(state.nbVisits == 12);

    PICOTEST_VERIFY(state.visits[0].metadata =
                        PICOTEST_METADATA(doTraverseSuite));
    {
        PICOTEST_VERIFY(state.visits[1].metadata =
                            PICOTEST_METADATA(doTraverseCase1));
        PICOTEST_VERIFY(state.visits[2].metadata =
                            PICOTEST_METADATA(doTraverseCase1));

        PICOTEST_VERIFY(state.visits[3].metadata =
                            PICOTEST_METADATA(doTraverseSubsuite));
        {
            PICOTEST_VERIFY(state.visits[4].metadata =
                                PICOTEST_METADATA(doTraverseSubcase1));
            PICOTEST_VERIFY(state.visits[5].metadata =
                                PICOTEST_METADATA(doTraverseSubcase1));

            PICOTEST_VERIFY(state.visits[6].metadata =
                                PICOTEST_METADATA(doTraverseSubcase2));
            PICOTEST_VERIFY(state.visits[7].metadata =
                                PICOTEST_METADATA(doTraverseSubcase2));
        }
        PICOTEST_VERIFY(state.visits[8].metadata =
                            PICOTEST_METADATA(doTraverseSubsuite));

        PICOTEST_VERIFY(state.visits[9].metadata =
                            PICOTEST_METADATA(doTraverseCase2));
        PICOTEST_VERIFY(state.visits[10].metadata =
                            PICOTEST_METADATA(doTraverseCase2));
    }
    PICOTEST_VERIFY(state.visits[11].metadata =
                        PICOTEST_METADATA(doTraverseSuite));
}