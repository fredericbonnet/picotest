# PicoTest: A minimalist unit testing framework for C programs

PicoTest is a single-file unit testing framework for C programs that follows
the xUnit principles:

https://en.wikipedia.org/wiki/XUnit


## License

PicoTest is released under the terms of the The 3-Clause BSD License:

https://opensource.org/licenses/BSD-3-Clause


## Installation

PicoTest is a single-file package, everything is defined in the header file
`picotest.h`. So you can either install this file in a standard location, or
copy it within your project source tree.


## Usage

Simply include the file in your source file, then start writing your tests!

```c
#include <picotest.h>
```

## Documentation

The HTML documentation is generated from its source using the great Doxygen
tool:

http://www.stack.nl/~dimitri/doxygen/

You can rebuild the documentation from scratch using the provided `Doxygen`
file.


## Examples

The `examples` subdirectory contains several example source files that
demonstrate the various features of PicoTest. These examples are also integrated
in the documentation.

Building the examples requires the CMake build tool along with your favorite
toolchain:

https://cmake.org/


## Integration with CMake

PicoTest provides  a CMake module definition for easier integration with
other CMake projects. In particular, it comes with an auto-discovery script for
CTest that makes use of the test traversal features of PicoTest.

The file `FindPicoTest.cmake` is the module definition. Add this file to your
`CMAKE_MODULE_PATH`, and add the following line to your CMake project:

```cmake
find_package(PicoTest)
``` 

You can then add the `PicoTest` dependency to your targets, e.g.:

```cmake
add_executable(my_test_runner)
target_link_libraries(my_test_runner
    PRIVATE PicoTest
)
``` 

If you also use CTest for test automation with `enable_testing()`, you can also call the provided `picotest_discover_tests` macro to integrate PicoTest test
cases in your build process automatically. For example, assuming that the
`my_test_runner` executable:

- when passed the `-l` option, will list all its test cases using the
  `PICOTEST_TRAVERSE` feature.
- when passed `<test_name>`, will execute the matching test case.

Then the following lines will:
1. execute `my_test_runner -l` as a post-build command to `my_test_runner`, 
2. add each discovered test case using `add_test(<test_name>)`,
3. when invoking the `test` rule, execute each test unitarily with
   `my_test_runner <test_name>`.

```cmake
enable_testing()
picotest_discover_tests(my_test_runner
    TEST_LIST_OPTION "-l"
)
``` 


## Development

PicoTest was developed on Windows 10 and Linux Ubuntu 16.04 using the following
tools:

- IDE: Visual Studio Code
- Build tool: CMake 3.11.0 
- Windows toolchain: Microsoft Visual C++ Build Tools 14
- Linux toolchain: GCC 5.4.0

It should work with any reasonably modern C compiler that supports variadic macros.

The assertion mechanism relies on `setjmp()` / `longjmp()`. While these
functions are discouraged for production code, their usage is acceptable in the
context of unit testing: in our case, `longjmp()` is only called when an
assertion fails, a situation where the actual process state is no longer
reliable anyway. Moreover, they constitute the only standard exception handling
mechanism for plain C code.
