#include <picotest.h>

#include "hooks.h"

PICOTEST_SUITE(mainSuite, testAssertions, testAssertionHooks, testCases,
               testCaseHooks, testFixtures, testFixtureHooks, testNamespaces,
               testSuites, testSuiteHooks, testFilters, testTraversal,
               testLoggers, testMetadata);

#define PICOTEST_MAINSUITE mainSuite
#include <picotestRunner.inc>
