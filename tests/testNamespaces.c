#include <picotest.h>
/*
 * Test suite for test namespaces
 */
#include "hooks.h"

PICOTEST_SUITE(testNamespaces, testNamespace1, testNamespace2, testNamespace3,
               testNamespace4);
