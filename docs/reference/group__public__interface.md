<a id="group__public__interface"></a>
# Public interface





## Submodules

* [Test Cases](group__test__cases.md#group__test__cases)
* [Assertions](group__assertions.md#group__assertions)
* [Test Fixtures](group__fixtures.md#group__fixtures)
* [Test Suites](group__test__suites.md#group__test__suites)

## Test Filters

PicoTest provides a way for client code to select tests to be run using custom filter functions.

<a id="group__public__interface_1gaf5acf1a68605f6c8b758bae0224e03fc"></a>
### Enumeration type PicoTestFilterResult

![][public]

**Definition**: `include/picotest.h` (line 176)


```cpp
enum PicoTestFilterResult {
  PICOTEST_FILTER_SKIP = 0,
  PICOTEST_FILTER_PASS = 1,
  PICOTEST_FILTER_SKIP_PROPAGATE = 2,
  PICOTEST_FILTER_PASS_PROPAGATE = 3
}
```


Result of test filter functions.

**Examples**:

[filter.c](filter_8c.md#filter_8c)   Example of PicoTest test filter, allows custom filtering of test functions.    <br/>
 [tags.c](tags_8c.md#tags_8c)   Advanced example of PicoTest test filter, implements a primitive tagging feature for test filtering.    <br/>



**See also**: [PicoTestFilterProc](group__public__interface.md#group__public__interface_1ga6d5c4a903f131bbed4913008d9e3b212)



<a id="group__public__interface_1ggaf5acf1a68605f6c8b758bae0224e03fca0ee37a1cf8a2347fb3c42636dfb80b1c"></a>
#### Enumerator PICOTEST\_FILTER\_SKIP

Test does not match the condition, skip this test and all its subtests.



<a id="group__public__interface_1ggaf5acf1a68605f6c8b758bae0224e03fca35508816a12c32e7ce536786e5ffc8d9"></a>
#### Enumerator PICOTEST\_FILTER\_PASS

Test matches the condition, run this test and all its subtests.



<a id="group__public__interface_1ggaf5acf1a68605f6c8b758bae0224e03fca487de7ecca4099ee737bd41a8d75ba75"></a>
#### Enumerator PICOTEST\_FILTER\_SKIP\_PROPAGATE

Test does not match the condition, skip this test but filter its subtests.



<a id="group__public__interface_1ggaf5acf1a68605f6c8b758bae0224e03fcaf2aa19fa3a0a1bc56585df626aa8e188"></a>
#### Enumerator PICOTEST\_FILTER\_PASS\_PROPAGATE

Test matches the condition, run this test but filter its subtests.



<a id="group__public__interface_1ga6d5c4a903f131bbed4913008d9e3b212"></a>
### Typedef PicoTestFilterProc

![][public]

**Definition**: `include/picotest.h` (line 216)


```cpp
typedef PicoTestFilterResult PicoTestFilterProc(PicoTestProc *test, const char *testName, const char *cond)
```


Signature of test filter functions.

A test called with a non- **NULL** condition must match this condition to be run. The test filter is set using the [PICOTEST\_FILTER](group__public__interface.md#group__public__interface_1gabd82de0bec174d972151cd122a0a03ff) macro.






**Parameters**:

* **test**: Test function to filter.
* **testName**: Name of test to filter.
* **cond**: Test filtering condition.


**Returns**:

a [PicoTestFilterResult](group__public__interface.md#group__public__interface_1gaf5acf1a68605f6c8b758bae0224e03fc) value


**Usage**:


```cpp
/* Custom test filter declaration. */
PicoTestFilterProc matchSubstring;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchSubstring

/* Test filter function. */
PicoTestFilterResult matchSubstring(PicoTestProc *test, const char *testName, const char *cond) {
    /* Match tests containing **cond** substring. */
    return (strstr(testName, cond) == NULL 
        ? PICOTEST_FILTER_SKIP_PROPAGATE 
        : PICOTEST_FILTER_PASS_PROPAGATE);
}
```


**Examples**:

[filter.c](filter_8c.md#filter_8c)   Example of PicoTest test filter, allows custom filtering of test functions.    <br/>
 [tags.c](tags_8c.md#tags_8c)   Advanced example of PicoTest test filter, implements a primitive tagging feature for test filtering.    <br/>






**See also**: [PICOTEST\_SUITE](picotest_8h.md#group__test__suites_1ga7a9c873e5e377bd88fcc4849689c1e6f), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5), [PICOTEST\_FILTER](group__public__interface.md#group__public__interface_1gabd82de0bec174d972151cd122a0a03ff), [PicoTestFilterResult](group__public__interface.md#group__public__interface_1gaf5acf1a68605f6c8b758bae0224e03fc)



**Return type**: [PicoTestFilterResult](group__public__interface.md#group__public__interface_1gaf5acf1a68605f6c8b758bae0224e03fc)

<a id="group__public__interface_1gace2d0b7428d63b90190fe65b619a8680"></a>
### Function \_picoTest\_filterByName

![][private]
![][static]


```cpp
static PicoTestFilterResult _picoTest_filterByName(PicoTestProc *test, const char *testName, const char *cond)
```


Implementation of default test filter function.

Does a simple string equality test between **testName** and **cond**, and propagates to subtests if it doesn't match.









**See also**: [PicoTestFailureLoggerProc](group__public__interface.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00), [PICOTEST\_FAILURE\_LOGGER](group__public__interface.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48), [PICOTEST\_FAILURE\_LOGGER\_DEFAULT](group__public__interface.md#group__public__interface_1gaf08fabb517d01d11ce72614d1df51687)



**Parameters**:

* [PicoTestProc](group__public__interface.md#group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9) * **test**
* const char * **testName**
* const char * **cond**

**Return type**: [PicoTestFilterResult](group__public__interface.md#group__public__interface_1gaf5acf1a68605f6c8b758bae0224e03fc)

<a id="group__public__interface_1ga7dccbea985fb578ba6b7639fb66fc3ea"></a>
### Macro PICOTEST\_FILTER\_DEFAULT

![][public]


```cpp
#define PICOTEST_FILTER_DEFAULT
```


Default test filter function.

Does a simple string equality test between **testName** and **cond**, and propagates to subtests if it doesn't match.








**See also**: [PicoTestFilterProc](group__public__interface.md#group__public__interface_1ga6d5c4a903f131bbed4913008d9e3b212), [PICOTEST\_FILTER](group__public__interface.md#group__public__interface_1gabd82de0bec174d972151cd122a0a03ff)



<a id="group__public__interface_1gabd82de0bec174d972151cd122a0a03ff"></a>
### Macro PICOTEST\_FILTER

![][public]


```cpp
#define PICOTEST_FILTER
```


Define the test filter function.

Called before calling a test with a non- **NULL** condition.





The default filter does a simple string equality test between its **testName** and **cond** arguments, and propagates to subtests if it doesn't match. Redefine this macro to use a custom filter function, which must follow the [PicoTestFilterProc](group__public__interface.md#group__public__interface_1ga6d5c4a903f131bbed4913008d9e3b212) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Custom test filter declaration. */
PicoTestFilterProc matchSubstring;
#undef PICOTEST_FILTER
#define PICOTEST_FILTER matchSubstring

/* Test filter function. */
PicoTestFilterResult matchSubstring(PicoTestProc *test, const char *testName, const char *cond) {
    /* Match tests containing **cond** substring. */
    return (strstr(testName, cond) == NULL 
        ? PICOTEST_FILTER_SKIP_PROPAGATE 
        : PICOTEST_FILTER_PASS_PROPAGATE);
}
```


**Examples**:

[filter.c](filter_8c.md#filter_8c)   Example of PicoTest test filter, allows custom filtering of test functions.    <br/>
 [tags.c](tags_8c.md#tags_8c)   Advanced example of PicoTest test filter, implements a primitive tagging feature for test filtering.    <br/>




**See also**: [PicoTestFilterProc](group__public__interface.md#group__public__interface_1ga6d5c4a903f131bbed4913008d9e3b212), [PICOTEST\_FILTER\_DEFAULT](group__public__interface.md#group__public__interface_1ga7dccbea985fb578ba6b7639fb66fc3ea)



## Test hierarchy traversal

Tests can form hierarchies of test suites and test cases. PicoTest provides two ways to traverse such hierarchies with a simple visitor pattern. This can be used for e.g. test list discovery in build systems.

<a id="group__public__interface_1gad78162429011bb689a76e91530ac7a22"></a>
### Enumeration type PicoTestVisitStep

![][public]

**Definition**: `include/picotest.h` (line 348)


```cpp
enum PicoTestVisitStep {
  PICOTEST_VISIT_ENTER = 0,
  PICOTEST_VISIT_LEAVE = 1
}
```


Test visit step.

**See also**: [PicoTestVisitProc](group__public__interface.md#group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34), [PICOTEST\_VISIT](group__public__interface.md#group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f)



<a id="group__public__interface_1ggad78162429011bb689a76e91530ac7a22a2590077bf6aceab607a23c349140af25"></a>
#### Enumerator PICOTEST\_VISIT\_ENTER

Enter the test.



<a id="group__public__interface_1ggad78162429011bb689a76e91530ac7a22a70b432be5fb3de15623c7cb1562544d0"></a>
#### Enumerator PICOTEST\_VISIT\_LEAVE

Leave the test.



<a id="group__public__interface_1ga403413d76b48c48740171b3a234af5c5"></a>
### Typedef PicoTestTraverseProc

![][public]

**Definition**: `include/picotest.h` (line 300)


```cpp
typedef void PicoTestTraverseProc(const char *name, int nb)
```


Function signature of test traversal proc.

**Parameters**:

* **name**: Name of traversed test.
* **nb**: Number of subtests (zero for simple test cases, at least one for test suites).


**Usage**:


```cpp
/* Test traversal function declaration. */
PicoTestTraverseProc printTestCase;
PicoTestTraverseProc printTestName;

/* Traversal function, will print test cases only. */
void printTestCase(const char *name, int nb) {
    if (nb == 0) printf("%s\n", name);
}

/* Traversal function, will print all tests. */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}
```


**Examples**:

[traverse.c](traverse_8c.md#traverse_8c)   Example of PicoTest hierarchy traversal, prints traversed tests to stdout.    <br/>



**See also**: [PICOTEST\_TRAVERSE](group__public__interface.md#group__public__interface_1gaee8202c2543c7fb59fa08aec75b6cc63)



**Return type**: void

<a id="group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34"></a>
### Typedef PicoTestVisitProc

![][public]

**Definition**: `include/picotest.h` (line 367)


```cpp
typedef void PicoTestVisitProc(const PicoTestMetadata *metadata, PicoTestVisitStep step)
```


Function signature of test visit proc.

Proc is called once for each value of [PicoTestVisitStep](group__public__interface.md#group__public__interface_1gad78162429011bb689a76e91530ac7a22).






**Parameters**:

* **metadata**: Metadata of the visited test.
* **step**: Visit step.




**See also**: [PICOTEST\_VISIT](group__public__interface.md#group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f), [PicoTestVisitStep](group__public__interface.md#group__public__interface_1gad78162429011bb689a76e91530ac7a22)



**Return type**: void

<a id="group__public__interface_1gaacd9c37695afbb5b3bb8c5373c527641"></a>
### Function \_picoTest\_traverse

![][private]
![][static]


```cpp
static void _picoTest_traverse(const PicoTestMetadata *metadata, PicoTestTraverseProc *proc)
```


Perform test traversal.

**Parameters**:

* **metadata**: Metadata of test to traverse.
* **proc**: Test traversal proc.





**See also**: [PicoTestTraverseProc](group__public__interface.md#group__public__interface_1ga403413d76b48c48740171b3a234af5c5), [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata), [PICOTEST\_TRAVERSE](group__public__interface.md#group__public__interface_1gaee8202c2543c7fb59fa08aec75b6cc63)



**Parameters**:

* const [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata) * **metadata**
* [PicoTestTraverseProc](group__public__interface.md#group__public__interface_1ga403413d76b48c48740171b3a234af5c5) * **proc**

**Return type**: void

<a id="group__public__interface_1ga114c577e2b5e238b8545c80be5783fea"></a>
### Function \_picoTest\_visit

![][private]
![][static]


```cpp
static void _picoTest_visit(const PicoTestMetadata *metadata, PicoTestVisitProc *proc)
```


Perform test visit.

**Parameters**:

* **metadata**: Metadata of test to visit.
* **proc**: Test visit proc.





**See also**: [PicoTestVisitProc](group__public__interface.md#group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34), [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata), [PICOTEST\_VISIT](group__public__interface.md#group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f)



**Parameters**:

* const [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata) * **metadata**
* [PicoTestVisitProc](group__public__interface.md#group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34) * **proc**

**Return type**: void

<a id="group__public__interface_1gaee8202c2543c7fb59fa08aec75b6cc63"></a>
### Macro PICOTEST\_TRAVERSE

![][public]


```cpp
#define PICOTEST_TRAVERSE( _testName ,_proc )
```


Traverse a test hierarchy depth-first.

This feature covers simple use cases such as getting the flat list of all test names. For more advanced usage, see [PICOTEST\_VISIT](group__public__interface.md#group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f).






**Parameters**:

* **_testName**: Name of the traversed test.
* **_proc**: Test traversal proc. Must follow the [PicoTestTraverseProc](group__public__interface.md#group__public__interface_1ga403413d76b48c48740171b3a234af5c5) signature.


**Examples**:

[traverse.c](traverse_8c.md#traverse_8c)   Example of PicoTest hierarchy traversal, prints traversed tests to stdout.    <br/>




**See also**: [PicoTestTraverseProc](group__public__interface.md#group__public__interface_1ga403413d76b48c48740171b3a234af5c5), [PICOTEST\_VISIT](group__public__interface.md#group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f)



<a id="group__public__interface_1ga84b8e9060ee56ca5c5b64da168ee7f6f"></a>
### Macro PICOTEST\_VISIT

![][public]


```cpp
#define PICOTEST_VISIT( _testName ,_proc )
```


Visit a test hierarchy depth-first.

This feature covers more advanced use cases than [PICOTEST\_TRAVERSE](group__public__interface.md#group__public__interface_1gaee8202c2543c7fb59fa08aec75b6cc63), such as exporting the test hierarchy as a structured format such as XML or JSON, or accessing test metadata.






**Parameters**:

* **_testName**: Name of the visited test.
* **_proc**: Test visit proc. Must follow the [PicoTestVisitProc](group__public__interface.md#group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34) signature.




**See also**: [PicoTestVisitProc](group__public__interface.md#group__public__interface_1ga2b14de2e8f56c8e7efb8e883069abb34), [PICOTEST\_TRAVERSE](group__public__interface.md#group__public__interface_1gaee8202c2543c7fb59fa08aec75b6cc63)



## Test Functions

<a id="group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9"></a>
### Typedef PicoTestProc

![][public]

**Definition**: `include/picotest.h` (line 105)


```cpp
typedef int PicoTestProc(const char *cond)
```


Signature of test functions.

Both [Test Suites](group__test__suites.md#group__test__suites) and [Test Cases](group__test__cases.md#group__test__cases) follow this signature.






**Parameters**:

* **cond**: Test filtering condition, or **NULL**. In the former case, passed to the active test filter before running the test.


**Returns**:

Number of failed tests.





**See also**: [PICOTEST\_SUITE](picotest_8h.md#group__test__suites_1ga7a9c873e5e377bd88fcc4849689c1e6f), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5), [PICOTEST\_FILTER](group__public__interface.md#group__public__interface_1gabd82de0bec174d972151cd122a0a03ff)



**Return type**: int

<a id="group__public__interface_1ga88033e8fb73d885670773cfc8ad1d024"></a>
### Macro PICOTEST\_EXTERN

![][public]


```cpp
#define PICOTEST_EXTERN( _testName )
```


Declare an extern test for metadata access.

**Parameters**:

* **_testName**: Test name.



**See also**: [PICOTEST\_METADATA](group__public__interface.md#group__public__interface_1gaa7f907387dd96cac614ad0dfe4cbb858)



<a id="group__public__interface_1gaa7f907387dd96cac614ad0dfe4cbb858"></a>
### Macro PICOTEST\_METADATA

![][public]


```cpp
#define PICOTEST_METADATA( _testName )
```


Get test metadata.

?> Tests in other modules need to be declared first with PICOTEST_EXTERN.


**Parameters**:

* **_testName**: Test name.




**See also**: [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata), [PICOTEST\_EXTERN](group__public__interface.md#group__public__interface_1ga88033e8fb73d885670773cfc8ad1d024)



## Logging

PicoTest provides a way for client code to intercept test failure events. This can be used for e.g. logging purpose or reporting.

<a id="group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00"></a>
### Typedef PicoTestFailureLoggerProc

![][public]

**Definition**: `include/picotest.h` (line 439)


```cpp
typedef void PicoTestFailureLoggerProc(const char *file, int line, const char *type, const char *test, const char *msg, va_list args)
```


Function signature of test failure log handlers.

**Parameters**:

* **file**: File name where the test was defined.
* **line**: Location of test in file.
* **type**: Type of test that failed (e.g. <code>"ASSERT"</code>).
* **test**: Tested expression.
* **msg**: Optional message format string, or **NULL**.
* **args**: Optional message string parameter list, or **NULL**.


?> **msg** and **args** are suitable arguments to **vprintf()**.


**Usage**:


```cpp
/* Test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test failure logger function. */
void logFailure(const char *file, int line, const char *type, const char *test, const char *msg, va_list args) {
    /* Error type. */
    printf("[%s] ", type);

    /* Location in source code. */
    printf("%s(%d) : ", file, line);

    /* Failed expression. */
    printf("%s", test);

    /* Optional message. */
    if (msg) {
        printf(" | "); 
        vprintf(msg, args);
    }

    printf("\n");
}
```


**Examples**:

[logger.c](logger_8c.md#logger_8c)   Example of PicoTest error logging, prints location and info of failed assertions to stdout.    <br/>



**See also**: [PICOTEST\_FAILURE\_LOGGER](group__public__interface.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48)



**Return type**: void

<a id="group__public__interface_1gae3c669f4ae731be32a25df3d3a97b599"></a>
### Function \_picoTest\_logFailure

![][private]
![][static]


```cpp
static void _picoTest_logFailure(const char *file, int line, const char *type, const char *test, const char *msg, va_list args)
```


Implementation of default test failure log handler.

Does nothing.









**See also**: [PicoTestFailureLoggerProc](group__public__interface.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00), [PICOTEST\_FAILURE\_LOGGER](group__public__interface.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48), [PICOTEST\_FAILURE\_LOGGER\_DEFAULT](group__public__interface.md#group__public__interface_1gaf08fabb517d01d11ce72614d1df51687)



**Parameters**:

* const char * **file**
* int **line**
* const char * **type**
* const char * **test**
* const char * **msg**
* va_list **args**

**Return type**: void

<a id="group__public__interface_1gaf08fabb517d01d11ce72614d1df51687"></a>
### Macro PICOTEST\_FAILURE\_LOGGER\_DEFAULT

![][public]


```cpp
#define PICOTEST_FAILURE_LOGGER_DEFAULT
```


Default test failure log handler.

Does nothing.








**See also**: [PicoTestFailureLoggerProc](group__public__interface.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00), [PICOTEST\_FAILURE\_LOGGER](group__public__interface.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48)



<a id="group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48"></a>
### Macro PICOTEST\_FAILURE\_LOGGER

![][public]


```cpp
#define PICOTEST_FAILURE_LOGGER
```


Define the test failure log handler.

Called when a test fails.





The default handler does nothing. Redefine this macro to use a custom handler, which must follow the [PicoTestFailureLoggerProc](group__public__interface.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Test failure logger declaration. */
PicoTestFailureLoggerProc logFailure;
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER logFailure

/* Test failure logger function. */
void logFailure(const char *file, int line, const char *type, const char *test, const char *msg, va_list args) {
    /* Error type. */
    printf("[%s] ", type);

    /* Location in source code. */
    printf("%s(%d) : ", file, line);

    /* Failed expression. */
    printf("%s", test);

    /* Optional message. */
    if (msg) {
        printf(" | "); 
        vprintf(msg, args);
    }

    printf("\n");
}
```


**Examples**:

[logger.c](logger_8c.md#logger_8c)   Example of PicoTest error logging, prints location and info of failed assertions to stdout.    <br/>




**See also**: [PicoTestFailureLoggerProc](group__public__interface.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00), [PICOTEST\_FAILURE\_LOGGER\_DEFAULT](group__public__interface.md#group__public__interface_1gaf08fabb517d01d11ce72614d1df51687)



## Version

PicoTest follows the Semantic Versioning Specification (SemVer) 2.0.0:





[https://semver.org/spec/v2.0.0.html](https://semver.org/spec/v2.0.0.html)

<a id="group__public__interface_1ga1402f3301dff3f468aac77622f877f2d"></a>
### Macro PICOTEST\_VERSION

![][public]


```cpp
#define PICOTEST_VERSION
```








<a id="group__public__interface_1ga9ea29549254cbe44f25ef974d0458e57"></a>
### Macro PICOTEST\_VERSION\_MAJOR

![][public]


```cpp
#define PICOTEST_VERSION_MAJOR
```








<a id="group__public__interface_1ga6488c76f8a06a1a8222c2309b170bd1d"></a>
### Macro PICOTEST\_VERSION\_MINOR

![][public]


```cpp
#define PICOTEST_VERSION_MINOR
```








<a id="group__public__interface_1gafc9d1ab6d8cced95f3560c3a006d8005"></a>
### Macro PICOTEST\_VERSION\_PATCH

![][public]


```cpp
#define PICOTEST_VERSION_PATCH
```








[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)
[private]: https://img.shields.io/badge/-private-red (private)
[static]: https://img.shields.io/badge/-static-lightgrey (static)