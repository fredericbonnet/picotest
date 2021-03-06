cmake_minimum_required(VERSION 3.11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

project(picotest_examples LANGUAGES C)

find_package(PicoTest)

add_executable(test_picotest)
target_sources(test_picotest
    PRIVATE
        main.c
        traverse.c
        hooks.c
        testAssertions.c
        testAssertionHooks.c
        testCases.c
        testCaseHooks.c
        testFixtures.c
        testFixtureHooks.c
        testSuites.c
        testSuiteHooks.c
        testFilters.c
        testTraversal.c
        testLoggers.c
        testMetadata.c
)
target_link_libraries(test_picotest
    PRIVATE
        PicoTest
)
enable_testing()
picotest_discover_tests(test_picotest
    TEST_LIST_OPTION "-l"
)
