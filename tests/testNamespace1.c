#define PICOTEST_NAMESPACE testNamespace1
#include <picotest.h>

/*
 * Test utilities
 */

static int testCalled;
PICOTEST_SUITE(doTestSuite, doTestCase1, doTestCase2, doTestCase3);
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

/*
 * Test suite for test modules
 */
#include "hooks.h"

PICOTEST_SUITE(testNamespace1, testSuiteShouldBeNamespaced);

PICOTEST_CASE(testSuiteShouldBeNamespaced) {
    testCalled = 0;
    testNamespace1_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 3);
}

PICOTEST_EXPORT(testNamespace1);
