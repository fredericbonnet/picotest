#define PICOTEST_NAMESPACE testNamespace4
#include <picotest.h>

/*
 * Test utilities
 */

static int testCalled;
PICOTEST_SUITE(doTestSuite, doTestCase1);
PICOTEST_CASE(doTestCase1) {
    testCalled++;
    PICOTEST_ASSERT(1);
}

/*
 * Test suite for test modules
 */
#include "hooks.h"

PICOTEST_SUITE(testNamespace4, testSubsuite1, testSubsuite2)

PICOTEST_SUITE(testSubsuite1, testCase1, testCase2);
PICOTEST_SUITE(testSubsuite2, testCase3, testCase4);
PICOTEST_CASE(testCase1) {
    testCalled = 0;
    testNamespace4_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 1);
}
PICOTEST_CASE(testCase2) {
    testCalled = 0;
    testNamespace4_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 1);
}
PICOTEST_CASE(testCase3) {
    testCalled = 0;
    testNamespace4_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 1);
}
PICOTEST_CASE(testCase4) {
    testCalled = 0;
    testNamespace4_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 1);
}

PICOTEST_EXPORT(testNamespace4);
