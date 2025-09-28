<a id="group__test__suites"></a>
# Test Suites



A test suite is a set of subtests in no special order. These subtests can themselves be test suites or test cases.

## Test Suite Hooks

PicoTest provides a way for client code to intercept test execution events on test suites and their subtests. This can be used for e.g. logging purpose or reporting.

<a id="group__test__suites_1ga4e09d95df5430205a201b5a02b522f25"></a>
### Typedef PicoTestSuiteEnterProc

![][public]

**Definition**: `include/picotest.h` (line 1568)


```cpp
typedef void PicoTestSuiteEnterProc(const char *suiteName, int nb)
```


Function signature of test suite enter hooks.

Called before running the first subtest.






**Parameters**:

* **suiteName**: Test suite name.
* **nb**: Number of subtests.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteEnterProc enterTestSuite;
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER enterTestSuite

/* Hook function. */
void enterTestSuite(const char *suiteName, int nb) {
    indent(level++);
    printf("running test suite %s (%d subtests)...\n", suiteName, nb);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_SUITE\_ENTER](picotest_8h.md#group__test__suites_1gae569b3a4f05ebefc297411072e505fd3)



**Return type**: void

<a id="group__test__suites_1ga5d8415df8755804fe1479ff21d17ed90"></a>
### Typedef PicoTestSuiteLeaveProc

![][public]

**Definition**: `include/picotest.h` (line 1616)


```cpp
typedef void PicoTestSuiteLeaveProc(const char *suiteName, int nb, int fail)
```


Function signature of test suite leave hooks.

**Parameters**:

* **suiteName**: Test suite name.
* **nb**: Number of subtests.
* **fail**: Number of failed subtests (including the subtests' subtests if any).


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteLeaveProc leaveTestSuite;
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_SUITE_LEAVE leaveTestSuite

/* Hook function. */
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    indent(--level);
    printf("test suite %s done (%d failures)\n", suiteName, fail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_SUITE\_LEAVE](picotest_8h.md#group__test__suites_1ga2ce5e2f78882e9f26067dc4ca9d0570c)



**Return type**: void

<a id="group__test__suites_1ga7547327d267d2bad9362c7adcc96bb24"></a>
### Typedef PicoTestSuiteBeforeSubtestProc

![][public]

**Definition**: `include/picotest.h` (line 1670)


```cpp
typedef void PicoTestSuiteBeforeSubtestProc(const char *suiteName, int nb, int fail, int index, const char *testName)
```


Function signature of test suite before subtest hooks.

Called before running each subtest.






**Parameters**:

* **suiteName**: Test suite name.
* **nb**: Number of subtests.
* **fail**: Failed test suite subtests so far (including its subtests' subtests if any).
* **index**: Index of subtest.
* **testName**: Name of subtest.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteBeforeSubtestProc beforeSubtest;
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#define PICOTEST_SUITE_BEFORE_SUBTEST beforeSubtest

/* Hook function. */
void beforeSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName) {
    indent(level++);
    printf("subtest %s (%d out of %d)...\n", testName, index+1, nb);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_SUITE\_BEFORE\_SUBTEST](picotest_8h.md#group__test__suites_1ga5a49439f633f383f0bb3d2a6e700d464)



**Return type**: void

<a id="group__test__suites_1gabce697eb4326140f89b0546d773da31c"></a>
### Typedef PicoTestSuiteAfterSubtestProc

![][public]

**Definition**: `include/picotest.h` (line 1727)


```cpp
typedef void PicoTestSuiteAfterSubtestProc(const char *suiteName, int nb, int fail, int index, const char *testName, int sfail)
```


Function signature of test suite after subtest hooks.

Called before running each subtest.






**Parameters**:

* **suiteName**: Test suite name.
* **nb**: Number of subtests.
* **fail**: Failed test suite subtests so far (including its subtests' subtests if any).
* **index**: Index of subtest.
* **testName**: Name of subtest.
* **sfail**: The subtest's failed tests (including its subtests if any).


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteAfterSubtestProc afterSubtest;
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_AFTER_SUBTEST afterSubtest

/* Hook function. */
void afterSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName, int sfail) {
    indent(--level);
    printf("=> subtest %s done (%d failed)...\n", testName, sfail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_SUITE\_AFTER\_SUBTEST](picotest_8h.md#group__test__suites_1gaab4493d86071cc9263827bf9a05a3b24)



**Return type**: void

<a id="group__test__suites_1ga50f13419afbe35f17150bacd7a906838"></a>
### Macro PICOTEST\_SUITE\_ENTER\_DEFAULT

![][public]


```cpp
#define PICOTEST_SUITE_ENTER_DEFAULT( suiteName ,nb )
```


Default test suite enter hook.

Does nothing.








**See also**: [PicoTestSuiteEnterProc](picotest_8h.md#group__test__suites_1ga4e09d95df5430205a201b5a02b522f25), [PICOTEST\_SUITE\_ENTER](picotest_8h.md#group__test__suites_1gae569b3a4f05ebefc297411072e505fd3)



<a id="group__test__suites_1gae569b3a4f05ebefc297411072e505fd3"></a>
### Macro PICOTEST\_SUITE\_ENTER

![][public]


```cpp
#define PICOTEST_SUITE_ENTER
```


Define the test suite enter hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestSuiteEnterProc](picotest_8h.md#group__test__suites_1ga4e09d95df5430205a201b5a02b522f25) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteEnterProc enterTestSuite;
#undef PICOTEST_SUITE_ENTER
#define PICOTEST_SUITE_ENTER enterTestSuite

/* Hook function. */
void enterTestSuite(const char *suiteName, int nb) {
    indent(level++);
    printf("running test suite %s (%d subtests)...\n", suiteName, nb);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestSuiteEnterProc](picotest_8h.md#group__test__suites_1ga4e09d95df5430205a201b5a02b522f25), [PICOTEST\_SUITE\_ENTER\_DEFAULT](picotest_8h.md#group__test__suites_1ga50f13419afbe35f17150bacd7a906838), [PICOTEST\_SUITE\_LEAVE](picotest_8h.md#group__test__suites_1ga2ce5e2f78882e9f26067dc4ca9d0570c)



<a id="group__test__suites_1gaf24c1f7c243e1990463aea4fbd4d5324"></a>
### Macro PICOTEST\_SUITE\_LEAVE\_DEFAULT

![][public]


```cpp
#define PICOTEST_SUITE_LEAVE_DEFAULT( suiteName ,nb ,fail )
```


Default test suite leave hook.

Does nothing.








**See also**: [PicoTestSuiteLeaveProc](picotest_8h.md#group__test__suites_1ga5d8415df8755804fe1479ff21d17ed90), [PICOTEST\_SUITE\_LEAVE](picotest_8h.md#group__test__suites_1ga2ce5e2f78882e9f26067dc4ca9d0570c)



<a id="group__test__suites_1ga2ce5e2f78882e9f26067dc4ca9d0570c"></a>
### Macro PICOTEST\_SUITE\_LEAVE

![][public]


```cpp
#define PICOTEST_SUITE_LEAVE
```


Define the test suite leave hook.

Called after running all subtests.





The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestSuiteLeaveProc](picotest_8h.md#group__test__suites_1ga5d8415df8755804fe1479ff21d17ed90) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteLeaveProc leaveTestSuite;
#undef PICOTEST_SUITE_LEAVE
#define PICOTEST_SUITE_LEAVE leaveTestSuite

/* Hook function. */
void leaveTestSuite(const char *suiteName, int nb, int fail) {
    indent(--level);
    printf("test suite %s done (%d failures)\n", suiteName, fail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestSuiteLeaveProc](picotest_8h.md#group__test__suites_1ga5d8415df8755804fe1479ff21d17ed90), [PICOTEST\_SUITE\_LEAVE\_DEFAULT](picotest_8h.md#group__test__suites_1gaf24c1f7c243e1990463aea4fbd4d5324), [PICOTEST\_SUITE\_ENTER](picotest_8h.md#group__test__suites_1gae569b3a4f05ebefc297411072e505fd3)



<a id="group__test__suites_1gab5b747836950016e04544e29879f3da3"></a>
### Macro PICOTEST\_SUITE\_BEFORE\_SUBTEST\_DEFAULT

![][public]


```cpp
#define PICOTEST_SUITE_BEFORE_SUBTEST_DEFAULT( suiteName ,nb ,fail ,index ,testName )
```


Default test suite before subtest hook.

Does nothing.








**See also**: [PicoTestSuiteBeforeSubtestProc](picotest_8h.md#group__test__suites_1ga7547327d267d2bad9362c7adcc96bb24), [PICOTEST\_SUITE\_BEFORE\_SUBTEST](picotest_8h.md#group__test__suites_1ga5a49439f633f383f0bb3d2a6e700d464)



<a id="group__test__suites_1ga5a49439f633f383f0bb3d2a6e700d464"></a>
### Macro PICOTEST\_SUITE\_BEFORE\_SUBTEST

![][public]


```cpp
#define PICOTEST_SUITE_BEFORE_SUBTEST
```


Define the test suite before subset hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestSuiteBeforeSubtestProc](picotest_8h.md#group__test__suites_1ga7547327d267d2bad9362c7adcc96bb24) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteBeforeSubtestProc beforeSubtest;
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#define PICOTEST_SUITE_BEFORE_SUBTEST beforeSubtest

/* Hook function. */
void beforeSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName) {
    indent(level++);
    printf("subtest %s (%d out of %d)...\n", testName, index+1, nb);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestSuiteBeforeSubtestProc](picotest_8h.md#group__test__suites_1ga7547327d267d2bad9362c7adcc96bb24), [PICOTEST\_SUITE\_BEFORE\_SUBTEST\_DEFAULT](picotest_8h.md#group__test__suites_1gab5b747836950016e04544e29879f3da3), [PICOTEST\_SUITE\_AFTER\_SUBTEST](picotest_8h.md#group__test__suites_1gaab4493d86071cc9263827bf9a05a3b24)



<a id="group__test__suites_1ga0aa7b03502294fee8f3e5b4951027145"></a>
### Macro PICOTEST\_SUITE\_AFTER\_SUBTEST\_DEFAULT

![][public]


```cpp
#define PICOTEST_SUITE_AFTER_SUBTEST_DEFAULT( suiteName ,nb ,fail ,index ,testName ,sfail )
```


Default test suite after subtest hook.

Does nothing.








**See also**: [PicoTestSuiteAfterSubtestProc](picotest_8h.md#group__test__suites_1gabce697eb4326140f89b0546d773da31c), [PICOTEST\_SUITE\_AFTER\_SUBTEST](picotest_8h.md#group__test__suites_1gaab4493d86071cc9263827bf9a05a3b24)



<a id="group__test__suites_1gaab4493d86071cc9263827bf9a05a3b24"></a>
### Macro PICOTEST\_SUITE\_AFTER\_SUBTEST

![][public]


```cpp
#define PICOTEST_SUITE_AFTER_SUBTEST
```


Define the test suite after subset hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestSuiteAfterSubtestProc](picotest_8h.md#group__test__suites_1gabce697eb4326140f89b0546d773da31c) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestSuiteAfterSubtestProc afterSubtest;
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_AFTER_SUBTEST afterSubtest

/* Hook function. */
void afterSubtest(const char *suiteName, int nb, int fail, int index, 
        const char *testName, int sfail) {
    indent(--level);
    printf("=> subtest %s done (%d failed)...\n", testName, sfail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestSuiteAfterSubtestProc](picotest_8h.md#group__test__suites_1gabce697eb4326140f89b0546d773da31c), [PICOTEST\_SUITE\_AFTER\_SUBTEST\_DEFAULT](picotest_8h.md#group__test__suites_1ga0aa7b03502294fee8f3e5b4951027145), [PICOTEST\_SUITE\_BEFORE\_SUBTEST](picotest_8h.md#group__test__suites_1ga5a49439f633f383f0bb3d2a6e700d464)



## Test Suite Definitions

<a id="group__test__suites_1ga7a9c873e5e377bd88fcc4849689c1e6f"></a>
### Macro PICOTEST\_SUITE

![][public]


```cpp
#define PICOTEST_SUITE( _suiteName ,... )
```


Test suite declaration.

A test suite is a test function that is made of one or several subtests.





This macro defines a [PicoTestProc](group__public__interface.md#group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9) of the given name that can be called directly.






**Parameters**:

* **_suiteName**: Name of the test suite.
* **...**: Names of the subtests in the suite.


**Returns**:

Number of failed tests.




**Usage**:


```cpp
/* Main test suite */
PICOTEST_SUITE(mainSuite, 
    testCase1, testCase2, subSuite, testCase3
)

/* Sub-suite */
PICOTEST_SUITE(subSuite, 
    testCase4, testCase5
)
```


**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>


**See also**: [PicoTestProc](group__public__interface.md#group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)
[private]: https://img.shields.io/badge/-private-red (private)
[static]: https://img.shields.io/badge/-static-lightgrey (static)