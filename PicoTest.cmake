# Adapted from GoogleTest.cmake
# Original Copyright notice:
#
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
PicoTest
--------

This module defines functions to help use the PicoTest infrastructure.

The  :command:`picotest_discover_tests` discovers tests by asking the
compiled test executable to enumerate its tests.  This is more robust and
provides better handling of parameterized tests, and does not require CMake
to be re-run when tests change.  However, it may not work in a cross-compiling
environment, and setting test properties is less convenient.

More details can be found in the documentation of the respective functions.

This command is intended to replace use of :command:`add_test` to register
tests, and will create a separate CTest test for each PicoTest test case.
Note that this is in some cases less efficient, as common set-up and tear-down
logic cannot be shared by multiple test cases executing in the same instance.
However, it provides more fine-grained pass/fail information to CTest, which is
usually considered as more beneficial.  By default, the CTest test name is the
same as the PicoTest name (i.e. ``testSuite`` or ``testCase``); see also
``TEST_PREFIX`` and ``TEST_SUFFIX``.

.. command:: picotest_discover_tests

  Automatically add tests with CTest by querying the compiled test executable
  for available tests::

    picotest_discover_tests(target
                         [EXTRA_ARGS arg1...]
                         [WORKING_DIRECTORY dir]
                         [TEST_LIST_OPTION option]
                         [TEST_PREFIX prefix]
                         [TEST_SUFFIX suffix]
                         [PROPERTIES name1 value1...]
                         [TEST_LIST var]
                         [DISCOVERY_TIMEOUT seconds]
    )

  ``picotest_discover_tests`` sets up a post-build command on the test 
  executable that generates the list of tests by parsing the output from running
  the test with the ``TEST_LIST_OPTION`` option .  This ensures that the full 
  list of tests, including instantiations of parameterized tests, is obtained.
  Since test discovery occurs at build time, it is not necessary to re-run CMake
  when the list of tests changes.
  However, it requires that :prop_tgt:`CROSSCOMPILING_EMULATOR` is properly set
  in order to function in a cross-compiling environment.

  Additionally, setting properties on tests is somewhat less convenient, since
  the tests are not available at CMake time.  Additional test properties may be
  assigned to the set of tests as a whole using the ``PROPERTIES`` option.  If
  more fine-grained test control is needed, custom content may be provided
  through an external CTest script using the :prop_dir:`TEST_INCLUDE_FILES`
  directory property.  The set of discovered tests is made accessible to such a
  script via the ``<target>_TESTS`` variable.

  The options are:

  ``target``
    Specifies the PicoTest executable, which must be a known CMake
    executable target.  CMake will substitute the location of the built
    executable when running the test.

  ``EXTRA_ARGS arg1...``
    Any extra arguments to pass on the command line to each test case.

  ``WORKING_DIRECTORY dir``
    Specifies the directory in which to run the discovered test cases.  If this
    option is not provided, the current binary directory is used.

  ``TEST_LIST_OPTION option``
    Specifies the command line option passed to the PicoTest executable so that
    it prints the list of test cases.

  ``TEST_PREFIX prefix``
    Specifies a ``prefix`` to be prepended to the name of each discovered test
    case.  This can be useful when the same test executable is being used in
    multiple calls to ``picotest_discover_tests()`` but with different
    ``EXTRA_ARGS``.

  ``TEST_SUFFIX suffix``
    Similar to ``TEST_PREFIX`` except the ``suffix`` is appended to the name of
    every discovered test case.  Both ``TEST_PREFIX`` and ``TEST_SUFFIX`` may
    be specified.

  ``PROPERTIES name1 value1...``
    Specifies additional properties to be set on all tests discovered by this
    invocation of ``picotest_discover_tests``.

  ``TEST_LIST var``
    Make the list of tests available in the variable ``var``, rather than the
    default ``<target>_TESTS``.  This can be useful when the same test
    executable is being used in multiple calls to ``picotest_discover_tests()``.
    Note that this variable is only available in CTest.

  ``DISCOVERY_TIMEOUT num``
    Specifies how long (in seconds) CMake will wait for the test to enumerate
    available tests.  If the test takes longer than this, discovery (and your
    build) will fail.  Most test executables will enumerate their tests very
    quickly, but under some exceptional circumstances, a test may require a
    longer timeout.  The default is 5.  See also the ``TIMEOUT`` option of
    :command:`execute_process`.

#]=======================================================================]

#------------------------------------------------------------------------------
function(picotest_discover_tests TARGET)
  cmake_parse_arguments(
    ""
    ""
    "TEST_LIST_OPTION;TEST_PREFIX;TEST_SUFFIX;WORKING_DIRECTORY;TEST_LIST;DISCOVERY_TIMEOUT"
    "EXTRA_ARGS;PROPERTIES"
    ${ARGN}
  )
  
  if(NOT _WORKING_DIRECTORY)
    set(_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  endif()
  if(NOT _TEST_LIST)
    set(_TEST_LIST ${TARGET}_TESTS)
  endif()
  if(NOT _DISCOVERY_TIMEOUT)
    set(_DISCOVERY_TIMEOUT 5)
  endif()

  get_property(
    has_counter
    TARGET ${TARGET}
    PROPERTY CTEST_DISCOVERED_TEST_COUNTER
    SET
  )
  if(has_counter)
    get_property(
      counter
      TARGET ${TARGET}
      PROPERTY CTEST_DISCOVERED_TEST_COUNTER
    )
    math(EXPR counter "${counter} + 1")
  else()
    set(counter 1)
  endif()
  set_property(
    TARGET ${TARGET}
    PROPERTY CTEST_DISCOVERED_TEST_COUNTER
    ${counter}
  )

  # Define rule to generate test list for aforementioned test executable
  set(ctest_file_base "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}[${counter}]")
  set(ctest_include_file "${ctest_file_base}_include.cmake")
  set(ctest_tests_file "${ctest_file_base}_tests.cmake")
  get_property(crosscompiling_emulator
    TARGET ${TARGET}
    PROPERTY CROSSCOMPILING_EMULATOR
  )
  add_custom_command(
    TARGET ${TARGET} POST_BUILD
    BYPRODUCTS "${ctest_tests_file}"
    COMMAND "${CMAKE_COMMAND}"
            -D "TEST_TARGET=${TARGET}"
            -D "TEST_EXECUTABLE=$<TARGET_FILE:${TARGET}>"
            -D "TEST_LIST_OPTION=${_TEST_LIST_OPTION}"
            -D "TEST_EXECUTOR=${crosscompiling_emulator}"
            -D "TEST_WORKING_DIR=${_WORKING_DIRECTORY}"
            -D "TEST_EXTRA_ARGS=${_EXTRA_ARGS}"
            -D "TEST_PROPERTIES=${_PROPERTIES}"
            -D "TEST_PREFIX=${_TEST_PREFIX}"
            -D "TEST_SUFFIX=${_TEST_SUFFIX}"
            -D "TEST_LIST=${_TEST_LIST}"
            -D "CTEST_FILE=${ctest_tests_file}"
            -D "TEST_DISCOVERY_TIMEOUT=${_DISCOVERY_TIMEOUT}"
            -P "${_PICOTEST_DISCOVER_TESTS_SCRIPT}"
    VERBATIM
    )

  file(WRITE "${ctest_include_file}"
    "if(EXISTS \"${ctest_tests_file}\")\n"
    "  include(\"${ctest_tests_file}\")\n"
    "else()\n"
    "  add_test(${TARGET}_NOT_BUILT ${TARGET}_NOT_BUILT)\n"
    "endif()\n"
  )

  # Add discovered tests to directory TEST_INCLUDE_FILES
  set_property(DIRECTORY
    APPEND PROPERTY TEST_INCLUDE_FILES "${ctest_include_file}"
  )

endfunction()

###############################################################################

set(_PICOTEST_DISCOVER_TESTS_SCRIPT
  ${CMAKE_CURRENT_LIST_DIR}/PicoTestAddTests.cmake
)
