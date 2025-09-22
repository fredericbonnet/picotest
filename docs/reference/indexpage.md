<a id="indexpage"></a>
# PicoTest: A minimalist unit testing framework for C programs



<a id="index_1md__r_e_a_d_m_e"></a>






PicoTest is a single-file unit testing framework for C programs that follows the xUnit principles:





[https://en.wikipedia.org/wiki/XUnit](https://en.wikipedia.org/wiki/XUnit)





## License

PicoTest is released under the terms of the 3-Clause BSD License:





[https://opensource.org/licenses/BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause)




## Installation

PicoTest is a single-file package, everything is defined in the header file <code>[picotest.h](picotest_8h.md#picotest_8h)</code>. So you can either install this file in a standard location, or copy it within your project source tree.




## Usage

Simply include the file in your source file, then start writing your tests!






```
#include <picotest.h>
```




## Documentation

The complete documentation is available here:





[https://fredericbonnet.github.io/picotest](https://fredericbonnet.github.io/picotest)





The documentation site was built using these great tools:






* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) extracts the documentation from the source code as both HTML and XML formats (the raw HTML output is available [here](https://fredericbonnet.github.io/picotest/html/index.html))

* [seaborg](https://github.com/fredericbonnet/seaborg) converts the XML files to Markdown (full disclosure: I'm the author of this tool!)

* [docsify](https://docsify.js.org/) generates the documentation site from the Markdown files







To rebuild the documentation you'll need the following tools:






* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) to process the provided <code>Doxyfile</code> and parse the source code

* [Node.js](https://nodejs.org/) to run the build scripts:








```
npm run docs
```






If you want to serve the documentation locally you can use the provided script:






```
npm run docsify
```




## Examples

The <code>examples</code> subdirectory contains several example source files that demonstrate the various features of PicoTest. These examples are also integrated in the documentation.





Building the examples requires the CMake build tool along with your favorite toolchain:





[https://cmake.org/](https://cmake.org/)




## Tests

PicoTest is self-tested and comes with a complete test suite that covers all aspects of the framework. This guarantees that PicoTest is production-ready.





The test suite itself is a good real-world example of PicoTest in action.





Building and running the test suite requires CMake (see next section for more information). To build the suite:






```
cd tests
cmake -S . -B build
cmake --build build
```






The build process makes use of the test discovery mechanism described in the next section.





To run the suite using CTest:






```
cd tests/build
ctest
```






You can also run the suite executable <code>test_picotest</code> directly from the CMake output directory.




## Integration with CMake

PicoTest provides a CMake package definition for easier integration with other CMake projects. In particular, it comes with an auto-discovery script for CTest that makes use of the test traversal features of PicoTest.





The file <code>PicoTestConfig.cmake</code> is the package config file at the root of the source repository. Add its path to your <code>CMAKE_PREFIX_PATH</code>, and add the following line to your CMake project:






```
find_package(PicoTest)
```






You can then add the <code>PicoTest::PicoTest</code> dependency to your targets, e.g.:






```
add_executable(my_test_runner)
target_link_libraries(my_test_runner
    PRIVATE PicoTest::PicoTest
)
```






If you also use CTest for test automation with <code>enable_testing()</code>, you can also call the provided <code>picotest_discover_tests</code> macro to integrate PicoTest test cases in your build process automatically. For example, assuming that the <code>my_test_runner</code> executable:






* when passed the <code>-l</code> option, will list all its test cases using the <code>PICOTEST_TRAVERSE</code> feature.

* when passed <code><test_name></code>, will execute the matching test case.







Then the following lines will:






1. execute <code>my_test_runner -l</code> as a post-build command to <code>my_test_runner</code>,

2. add each discovered test case using <code>add_test(<test_name>)</code>,

3. when invoking the <code>test</code> rule, execute each test unitarily with <code>my_test_runner <test_name></code>.








```
enable_testing()
picotest_discover_tests(my_test_runner
    TEST_LIST_OPTION "-l"
)
```




## Integration with Conan

PicoTest provides a Conan 2 recipe for easier dependency management. To create the PicoTest package locally:






```
conan create . --build=missing
```






You can then add it to your project requirements (<code>conanfile.txt</code>):






```
[requires]
picotest/1.4.3
```




## Development

PicoTest was developed on Windows 10 and Linux Ubuntu 16.04 using the following tools:






* IDE: Visual Studio Code

* Build tool: CMake 3.15.2

* Windows toolchain: Microsoft Visual C++ Build Tools 14

* Linux toolchain: GCC 5.4.0







It should work with any reasonably modern C compiler that supports variadic macros.





The assertion mechanism relies on <code>setjmp()</code> / <code>longjmp()</code>. While these functions are discouraged for production code, their usage is acceptable in the context of unit testing: in our case, <code>longjmp()</code> is only called when an assertion fails, a situation where the actual process state is no longer reliable anyway. Moreover, they constitute the only standard exception handling mechanism for plain C code.






```

```

**TODO**:

* location {"type":"element","name":"location","attributes":{"file":"README.md"},"children":[]}

[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)
[private]: https://img.shields.io/badge/-private-red (private)
[static]: https://img.shields.io/badge/-static-lightgrey (static)