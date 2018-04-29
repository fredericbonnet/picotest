# Adapted from GoogleTestAddTests.cmake
# Original Copyright notice:
#
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

set(list_option "${TEST_LIST_OPTION}")
set(prefix "${TEST_PREFIX}")
set(suffix "${TEST_SUFFIX}")
set(extra_args ${TEST_EXTRA_ARGS})
set(properties ${TEST_PROPERTIES})
set(script)
set(suite)
set(tests)

function(add_command NAME)
  set(_args "")
  foreach(_arg ${ARGN})
    if(_arg MATCHES "[^-./:a-zA-Z0-9_]")
      set(_args "${_args} [==[${_arg}]==]")
    else()
      set(_args "${_args} ${_arg}")
    endif()
  endforeach()
  set(script "${script}${NAME}(${_args})\n" PARENT_SCOPE)
endfunction()

# Run test executable to get list of available tests
if(NOT EXISTS "${TEST_EXECUTABLE}")
  message(FATAL_ERROR
    "Specified test executable does not exist.\n"
    "  Path: '${TEST_EXECUTABLE}'"
  )
endif()
execute_process(
  COMMAND ${TEST_EXECUTOR} "${TEST_EXECUTABLE}" "${list_option}"
  TIMEOUT ${TEST_DISCOVERY_TIMEOUT}
  OUTPUT_VARIABLE output
  RESULT_VARIABLE result
)
if(NOT ${result} EQUAL 0)
  string(REPLACE "\n" "\n    " output "${output}")
  message(FATAL_ERROR
    "Error running test executable.\n"
    "  Path: '${TEST_EXECUTABLE}'\n"
    "  Result: ${result}\n"
    "  Output:\n"
    "    ${output}\n"
  )
endif()

string(REPLACE "\n" ";" output "${output}")

# Parse output
foreach(line ${output})
  if(NOT line MATCHES "^$")
    # Test name; strip spaces...
    string(REGEX REPLACE " +" "" test "${line}")
    message(STATUS "Found test ${test}")
    # ...and add to script
    add_command(add_test
      "${prefix}${test}${suffix}"
      ${TEST_EXECUTOR}
      "${TEST_EXECUTABLE}"
      "${test}"
      ${extra_args}
    )
    message(STATUS "Added test ${prefix}${test}${suffix}")
    add_command(set_tests_properties
      "${prefix}${test}${suffix}"
      PROPERTIES
      WORKING_DIRECTORY "${TEST_WORKING_DIR}"
      ${properties}
    )
    list(APPEND tests "${prefix}${test}${suffix}")
  endif()
endforeach()

# Create a list of all discovered tests, which users may use to e.g. set
# properties on the tests
add_command(set ${TEST_LIST} ${tests})

# Write CTest script
file(WRITE "${CTEST_FILE}" "${script}")
