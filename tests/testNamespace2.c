#define PICOTEST_NAMESPACE testNamespace2
#define PICOTEST_NAMESPACE_DELIMITER "::"
#include <picotest.h>

/*
 * Test utilities
 */

static int testCalled;
PICOTEST_SUITE(doTestSuite, doTestCase1, doTestCase2);
PICOTEST_CASE(doTestCase1) {
    testCalled++;
    PICOTEST_ASSERT(1);
}
PICOTEST_CASE(doTestCase2) {
    testCalled++;
    PICOTEST_ASSERT(0);
}

/*
 * Test suite for test modules
 */
#include "hooks.h"

PICOTEST_SUITE(testNamespace2, testSuiteShouldBeNamespaced);

PICOTEST_CASE(testSuiteShouldBeNamespaced) {
    testCalled = 0;
    testNamespace2_doTestSuite(NULL); // Call namespaced suite
    PICOTEST_ASSERT(testCalled == 2);
}

PICOTEST_EXPORT(testNamespace2);