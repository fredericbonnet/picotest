#define PICOTEST_NAMESPACE testNamespace3
#include <picotest.h>

/*
 * Test utilities
 */

static int testCalled;
PICOTEST_SUITE(doTestSuite, doTestCase1, doTestCase2, doTestCase3, doTestCase4);
PICOTEST_CASE(doTestCase1) {
    testCalled++;
    PICOTEST_ASSERT(1);
}
PICOTEST_CASE(doTestCase2) {
    testCalled++;
    PICOTEST_ASSERT(0);
}
PICOTEST_CASE(doTestCase3) {
    testCalled++;
    PICOTEST_ASSERT(0);
}
PICOTEST_CASE(doTestCase4) {
    testCalled++;
    PICOTEST_ASSERT(0);
}

/*
 * Test suite for test modules
 */
#include "hooks.h"

PICOTEST_CASE(testNamespace3) {
    testCalled = 0;
    testNamespace3_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 4);
}

PICOTEST_EXPORT(testNamespace3);
