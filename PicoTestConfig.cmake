# PicoTest CMake configuration file
include(CMakeFindDependencyMacro)

# Set the path for PicoTestAddTests.cmake
set(_PICOTEST_DISCOVER_TESTS_SCRIPT 
    "${CMAKE_CURRENT_LIST_DIR}/PicoTestAddTests.cmake")

# Include the CMake functions
include("${CMAKE_CURRENT_LIST_DIR}/PicoTest.cmake")

# Create the target
if(NOT TARGET PicoTest::PicoTest)
    add_library(PicoTest::PicoTest INTERFACE IMPORTED)
    set_target_properties(PicoTest::PicoTest PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../include"
    )
endif()

# Set standard package variables
set(PicoTest_FOUND TRUE)
set(PicoTest_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include") 