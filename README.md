# PicoTest: A minimalist unit testing framework for C programs

PicoTest is a single-file unit testing framework for C programs that follows
the xUnit principles:

https://en.wikipedia.org/wiki/XUnit

## License

PicoTest is released under the terms of the 3-Clause BSD License:

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

The complete documentation is available here:

https://fredericbonnet.github.io/picotest

The documentation site was built using these great tools:

- [Doxygen] extracts the documentation from the source code as both HTML and XML
  formats (the raw HTML output is available [here][htmldocs])
- [seaborg] converts the XML files to Markdown (full disclosure: I'm the author
  of this tool!)
- [docsify] generates the documentation site from the Markdown files

To rebuild the documentation you'll need the following tools:

- [Doxygen] to process the provided `Doxyfile` and parse the source code
- [Node.js] to run the build scripts:

```sh
npm run docs
```

If you want to serve the documentation locally you can use the provided script:

```sh
npm run docsify
```

## Examples

The `examples` subdirectory contains several example source files that
demonstrate the various features of PicoTest. These examples are also integrated
in the documentation.

Building the examples requires the CMake build tool along with your favorite
toolchain:

https://cmake.org/

## Tests

PicoTest is self-tested and comes with a complete test suite that covers all
aspects of the framework. This guarantees that PicoTest is production-ready.

The test suite itself is a good real-world example of PicoTest in action.

Building and running the test suite requires CMake (see next section for more
information). To build the suite:

```sh
cd tests
cmake -S . -B build
cmake --build build
```

The build process makes use of the test discovery mechanism described in the
next section.

To run the suite using CTest:

```sh
cd tests/build
ctest
```

You can also run the suite executable `test_picotest` directly from the CMake
output directory.

## Package Management with Conan

The easiest way to use PicoTest in your projects is through [Conan](https://conan.io/) package management.

### Using PicoTest as a Dependency

Create a `conanfile.txt` in your project:

```ini
[requires]
picotest/1.4.2

[generators]
CMakeDeps
CMakeToolchain
```

Then in your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(my_tests LANGUAGES C)

find_package(PicoTest REQUIRED)

add_executable(my_test_runner test.c)
target_link_libraries(my_test_runner PRIVATE PicoTest::PicoTest)

# Optional: Enable automatic test discovery
enable_testing()
picotest_discover_tests(my_test_runner TEST_LIST_OPTION "-l")
```

Your `test.c`:

```c
#include <picotest.h>

PICOTEST_CASE(testExample) {
    PICOTEST_ASSERT(1 + 1 == 2, "Math should work");
}

PICOTEST_SUITE(testExample);

int main() {
    return picotest_main();
}
```

Build and run:

```bash
# Install dependencies
conan install . --output-folder=build --build=missing

# Configure and build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Run tests
cd build && ctest  # Or run your executable directly
```

### Modern Conan 2.x Workflow

For the cleanest experience with Conan 2.x, use the `--output-folder` flag to keep your project root clean:

```bash
# Clean build directory approach (recommended)
mkdir build
conan install . --output-folder=build --build=missing
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Local Development

For PicoTest development and local packaging:

```bash
# Create local package
conan create . --build=missing

# For development iteration
conan install . --output-folder=build --build=missing
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Publishing

To publish PicoTest to a Conan registry:

```bash
# Upload to your registry
conan upload picotest/1.4.2 --all -r=your-registry
```

### Troubleshooting

**Issue**: `picotest_discover_tests function not found`
```bash
# Solution: Ensure you're using find_package(PicoTest) and linking PicoTest::PicoTest
find_package(PicoTest REQUIRED)
target_link_libraries(your_target PRIVATE PicoTest::PicoTest)
```

**Issue**: `Cannot find package picotest/1.4.2`
```bash
# Solution: Create local package first
conan create . --build=missing
```

**Issue**: `Traditional CMake setup not working`
```bash
# Solution: Use CMAKE_PREFIX_PATH (not CMAKE_MODULE_PATH)
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/picotest
```

**Issue**: `Conan-generated files cluttering project root`
```bash
# Solution: Use --output-folder flag (Conan 2.x)
conan install . --output-folder=build --build=missing
```

**Issue**: `CMake can't find conan_toolchain.cmake`
```bash
# Solution: Ensure you're pointing to the correct toolchain file in build directory
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
```

## Integration with CMake

PicoTest also supports traditional CMake integration for manual setups.

Add PicoTest to your `CMAKE_PREFIX_PATH`, and add the following line to your CMake project:

```cmake
find_package(PicoTest)
```

To build with manual setup:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/picotest
cmake --build build --config Release
```

You can then add the `PicoTest::PicoTest` dependency to your targets, e.g.:

```cmake
add_executable(my_test_runner)
target_link_libraries(my_test_runner
    PRIVATE PicoTest::PicoTest
)
```

If you also use CTest for test automation with `enable_testing()`, you can also
call the provided `picotest_discover_tests` macro to integrate PicoTest test
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
- Build tool: CMake 3.15.2
- Windows toolchain: Microsoft Visual C++ Build Tools 14
- Linux toolchain: GCC 5.4.0

It should work with any reasonably modern C compiler that supports variadic
macros.

The assertion mechanism relies on `setjmp()` / `longjmp()`. While these
functions are discouraged for production code, their usage is acceptable in the
context of unit testing: in our case, `longjmp()` is only called when an
assertion fails, a situation where the actual process state is no longer
reliable anyway. Moreover, they constitute the only standard exception handling
mechanism for plain C code.

[docs]: https://fredericbonnet.github.io/picotest
[htmldocs]: https://fredericbonnet.github.io/picotest/html/index.html
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[seaborg]: https://github.com/fredericbonnet/seaborg
[docsify]: https://docsify.js.org/
[node.js]: https://nodejs.org/
