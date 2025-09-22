<a id="group__test__cases"></a>
# Test Cases



Test cases are the most elementary test functions. They are defined as simple functions blocks with assertions that checks the validity of the outcome.

## Test Case Hooks

PicoTest provides a way for client code to intercept test case events. This can be used for e.g. logging purpose or reporting.

<a id="group__test__cases_1ga2148fa53887bde18878299c0941d9844"></a>
### Typedef PicoTestCaseEnterProc

![][public]

**Definition**: `include/picotest.h` (line 634)


```cpp
typedef void PicoTestCaseEnterProc(const char *testName)
```


Function signature of test case enter hooks.

Called before running the test case.






**Parameters**:

* **testName**: Test case name.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestCaseEnterProc enterTestCase;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER enterTestCase

/* Hook function. */
void enterTestCase(const char *testName) {
    indent(level++);
    printf("running test case %s...\n", testName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_CASE\_ENTER](group__test__cases.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



**Return type**: void

<a id="group__test__cases_1ga2649b7563a8a3c14c93f310cb6699185"></a>
### Typedef PicoTestCaseLeaveProc

![][public]

**Definition**: `include/picotest.h` (line 682)


```cpp
typedef void PicoTestCaseLeaveProc(const char *testName, int fail)
```


Function signature of test case leave hooks.

Called after running the test case.






**Parameters**:

* **testName**: Test case name.
* **fail**: Failed tests (including its subtests if any).


**Usage**:


```cpp
/* Hook declarations. */
PicoTestCaseLeaveProc leaveTestCase;
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_LEAVE leaveTestCase

/* Hook function. */
void leaveTestCase(const char *testName, int fail) {
    indent(--level);
    printf("test case %s done (%d failures)\n", testName, fail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_CASE\_LEAVE](group__test__cases.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



**Return type**: void

<a id="group__test__cases_1ga4a4a1356f85b26cd29f2f7ae4c09cf91"></a>
### Macro PICOTEST\_CASE\_ENTER\_DEFAULT

![][public]


```cpp
#define PICOTEST_CASE_ENTER_DEFAULT( testName )
```


Default test case enter hook.

Does nothing.








**See also**: [PicoTestCaseEnterProc](group__test__cases.md#group__test__cases_1ga2148fa53887bde18878299c0941d9844), [PICOTEST\_CASE\_ENTER](group__test__cases.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



<a id="group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67"></a>
### Macro PICOTEST\_CASE\_ENTER

![][public]


```cpp
#define PICOTEST_CASE_ENTER
```


Define the test case enter hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestCaseEnterProc](group__test__cases.md#group__test__cases_1ga2148fa53887bde18878299c0941d9844) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestCaseEnterProc enterTestCase;
#undef PICOTEST_CASE_ENTER
#define PICOTEST_CASE_ENTER enterTestCase

/* Hook function. */
void enterTestCase(const char *testName) {
    indent(level++);
    printf("running test case %s...\n", testName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestCaseEnterProc](group__test__cases.md#group__test__cases_1ga2148fa53887bde18878299c0941d9844), [PICOTEST\_CASE\_ENTER\_DEFAULT](group__test__cases.md#group__test__cases_1ga4a4a1356f85b26cd29f2f7ae4c09cf91), [PICOTEST\_CASE\_LEAVE](group__test__cases.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



<a id="group__test__cases_1ga5ff2295c5a324991c72a81bcfb949522"></a>
### Macro PICOTEST\_CASE\_LEAVE\_DEFAULT

![][public]


```cpp
#define PICOTEST_CASE_LEAVE_DEFAULT( testName ,fail )
```


Default test case enter hook.

Does nothing.








**See also**: [PicoTestCaseLeaveProc](group__test__cases.md#group__test__cases_1ga2649b7563a8a3c14c93f310cb6699185), [PICOTEST\_CASE\_LEAVE](group__test__cases.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



<a id="group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a"></a>
### Macro PICOTEST\_CASE\_LEAVE

![][public]


```cpp
#define PICOTEST_CASE_LEAVE
```


Define the test case leave hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestCaseLeaveProc](group__test__cases.md#group__test__cases_1ga2649b7563a8a3c14c93f310cb6699185) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestCaseLeaveProc leaveTestCase;
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_LEAVE leaveTestCase

/* Hook function. */
void leaveTestCase(const char *testName, int fail) {
    indent(--level);
    printf("test case %s done (%d failures)\n", testName, fail);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestCaseLeaveProc](group__test__cases.md#group__test__cases_1ga2649b7563a8a3c14c93f310cb6699185), [PICOTEST\_CASE\_LEAVE\_DEFAULT](group__test__cases.md#group__test__cases_1ga5ff2295c5a324991c72a81bcfb949522), [PICOTEST\_CASE\_ENTER](group__test__cases.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



## Test Case Definitions

<a id="group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5"></a>
### Macro PICOTEST\_CASE

![][public]


```cpp
#define PICOTEST_CASE( ... )
```


Test case declaration.

This macro defines a [PicoTestProc](group__public__interface.md#group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9) of the given name that can be called directly.






**Parameters**:

* **_testName**: Name of the test case.
* **_fixtureName**: (optional) Name of the test fixture used by the test.
* **_context**: (optional) Fixture context structure defined using [PICOTEST\_FIXTURE\_CONTEXT(\_fixtureName)](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03).


**Returns**:

Number of failed tests.


**Usage**:


```cpp
#define FAILS 0
#define PASSES 1

/* Simple test with no fixture */
PICOTEST_CASE(testCase1) {
    PICOTEST_VERIFY(FAILS); /* Logs error and continue */
    PICOTEST_ASSERT(FAILS); /* Logs error and abort */
    /* Unreached */
    PICOTEST_ASSERT(PASSES);
}

/* Test with fixture but no context */
PICOTEST_CASE(testCase2, simpleFixture) {
    PICOTEST_ASSERT(staticVar == 1);    /* Passes */
    PICOTEST_VERIFY(FAILS);             /* Logs error and continue */
}

/* Test with fixture and context. Tests belonging to the same suite don't have
 * to share the same suite. */
PICOTEST_CASE(testCase3, fixtureWithContext, context) {
    PICOTEST_ASSERT(staticVar == 2);        /* Passes */
    PICOTEST_ASSERT(context->var1 == 1);    /* Passes */
    PICOTEST_VERIFY(context->var2 == NULL); /* Logs error and continue */
    PICOTEST_ASSERT(context->var3 == NULL); /* Logs error and abort */
}

/* Another test using **simpleFixture**. Tests need not belong to the same suite
 * to share a fixture. */
PICOTEST_CASE(testCase4, simpleFixture) {
    PICOTEST_VERIFY(staticVar == 1);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}

/* This test uses a fixture that requires a context. In this case the context
 * passed to the fixture setup and teardown functions is NULL. */
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}

```


**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>




**See also**: [PicoTestProc](group__public__interface.md#group__public__interface_1ga5c445b2f0ea8f269813f7e479753bff9), [PICOTEST\_FIXTURE\_CONTEXT](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03)



[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)
[private]: https://img.shields.io/badge/-private-red (private)
[static]: https://img.shields.io/badge/-static-lightgrey (static)