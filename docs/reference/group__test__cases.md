<a id="group__test__cases"></a>
# Test Cases



Test cases are the most elementary test functions. They are defined as simple functions blocks with assertions that checks the validity of the outcome.

## Test Case Definitions

<a id="group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5"></a>
### Macro PICOTEST\_CASE

![][public]

```cpp
#define PICOTEST_CASE( ... )
```

Test case declaration.

This macro defines a [PicoTestProc](picotest_8h.md#group__public__interface_1ga824e8707dfbd1726aa15beb5f27b957a) of the given name that can be called directly.






**Parameters**:

* **_testName**: Name of the test case.
* **_fixtureName**: (optional) Name of the test fixture used by the test.
* **_context**: (optional) Fixture context structure defined using [PICOTEST\_FIXTURE\_CONTEXT(\_fixtureName)](picotest_8h.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03).


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

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc) Example of a simple PicoTest suite.




**See also**: [PicoTestProc](picotest_8h.md#group__public__interface_1ga824e8707dfbd1726aa15beb5f27b957a), [PICOTEST\_FIXTURE\_CONTEXT](picotest_8h.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03)



## Test Case Hooks

PicoTest provides a way for client code to intercept test case events. This can be used for e.g. logging purpose or reporting.

<a id="group__test__cases_1ga0af0a0ec6d2bbee706b56fea6f60126e"></a>
### Typedef PicoTestCaseEnterProc

![][public]

**Definition**: `include/picotest.h` (line 636)

```cpp
typedef void() PicoTestCaseEnterProc(const char *testName)
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

[hooks.c](hooks_8c.md#hooks_8c) Example of PicoTest hooks, prints all events to stdout.



**See also**: [PICOTEST\_CASE\_ENTER](picotest_8h.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



**Return type**: void()

<a id="group__test__cases_1gacce6ae69ea5064e39e3c56915978609e"></a>
### Typedef PicoTestCaseLeaveProc

![][public]

**Definition**: `include/picotest.h` (line 684)

```cpp
typedef void() PicoTestCaseLeaveProc(const char *testName, int fail)
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

[hooks.c](hooks_8c.md#hooks_8c) Example of PicoTest hooks, prints all events to stdout.



**See also**: [PICOTEST\_CASE\_LEAVE](picotest_8h.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



**Return type**: void()

<a id="group__test__cases_1ga4a4a1356f85b26cd29f2f7ae4c09cf91"></a>
### Macro PICOTEST\_CASE\_ENTER\_DEFAULT

![][public]

```cpp
#define PICOTEST_CASE_ENTER_DEFAULT( testName )
```

Default test case enter hook.

Does nothing.








**See also**: [PicoTestCaseEnterProc](picotest_8h.md#group__test__cases_1ga0af0a0ec6d2bbee706b56fea6f60126e), [PICOTEST\_CASE\_ENTER](picotest_8h.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



<a id="group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67"></a>
### Macro PICOTEST\_CASE\_ENTER

![][public]

```cpp
#define PICOTEST_CASE_ENTER
```

Define the test case enter hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestCaseEnterProc](picotest_8h.md#group__test__cases_1ga0af0a0ec6d2bbee706b56fea6f60126e) signature.






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

[hooks.c](hooks_8c.md#hooks_8c) Example of PicoTest hooks, prints all events to stdout.





**See also**: [PicoTestCaseEnterProc](picotest_8h.md#group__test__cases_1ga0af0a0ec6d2bbee706b56fea6f60126e), [PICOTEST\_CASE\_ENTER\_DEFAULT](picotest_8h.md#group__test__cases_1ga4a4a1356f85b26cd29f2f7ae4c09cf91), [PICOTEST\_CASE\_LEAVE](picotest_8h.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



<a id="group__test__cases_1ga5ff2295c5a324991c72a81bcfb949522"></a>
### Macro PICOTEST\_CASE\_LEAVE\_DEFAULT

![][public]

```cpp
#define PICOTEST_CASE_LEAVE_DEFAULT( testName ,fail )
```

Default test case enter hook.

Does nothing.








**See also**: [PicoTestCaseLeaveProc](picotest_8h.md#group__test__cases_1gacce6ae69ea5064e39e3c56915978609e), [PICOTEST\_CASE\_LEAVE](picotest_8h.md#group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a)



<a id="group__test__cases_1ga4fd71dfed1ce3733b0d670c86b8d523a"></a>
### Macro PICOTEST\_CASE\_LEAVE

![][public]

```cpp
#define PICOTEST_CASE_LEAVE
```

Define the test case leave hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestCaseLeaveProc](picotest_8h.md#group__test__cases_1gacce6ae69ea5064e39e3c56915978609e) signature.






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

[hooks.c](hooks_8c.md#hooks_8c) Example of PicoTest hooks, prints all events to stdout.





**See also**: [PicoTestCaseLeaveProc](picotest_8h.md#group__test__cases_1gacce6ae69ea5064e39e3c56915978609e), [PICOTEST\_CASE\_LEAVE\_DEFAULT](picotest_8h.md#group__test__cases_1ga5ff2295c5a324991c72a81bcfb949522), [PICOTEST\_CASE\_ENTER](picotest_8h.md#group__test__cases_1gad1f702ab6600b04f66731d35bf38fc67)



[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)