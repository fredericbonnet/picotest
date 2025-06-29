<a id="group__assertions"></a>
# Assertions



Assertions are the basic building blocks of test cases.

## Assertion Hooks

PicoTest provides a way for client code to intercept assertions events. This can be used for e.g. logging purpose or reporting.

<a id="group__assertions_1ga507d93a48b3c01ec9c43499d129d6db0"></a>
### Typedef PicoTestAssertBeforeProc

![][public]

**Definition**: `include/picotest.h` (line 905)

```cpp
typedef void PicoTestAssertBeforeProc(const char *type, const char *test)
```

Function signature of assert before hooks.

Called before running an assertion.






**Parameters**:

* **type**: Type of test (e.g. "ASSERT").
* **test**: Test.


**Usage**:

```cpp
/* Hook declarations. */
PicoTestAssertBeforeProc beforeAssert;
#undef PICOTEST_ASSERT_BEFORE
#define PICOTEST_ASSERT_BEFORE beforeAssert

/* Hook function. */
void beforeAssert(const char *type, const char *test) {
    indent(level++);
    printf("before assertion %s(%s)...\n", type, test);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_ASSERT\_BEFORE](picotest_8h.md#group__assertions_1gaa38b1a0014fe2ab172a5466f9031aafb)



**Return type**: void

<a id="group__assertions_1ga8f5650aa00db35bc50511fa2a01a45e7"></a>
### Typedef PicoTestAssertAfterProc

![][public]

**Definition**: `include/picotest.h` (line 954)

```cpp
typedef void PicoTestAssertAfterProc(const char *type, const char *test, int fail)
```

Function signature of assert after hooks.

Called after running an assertion.






**Parameters**:

* **type**: Type of test (e.g. "ASSERT").
* **test**: Test.
* **fail**: Test result: zero for success, non-zero for failure.


**Usage**:

```cpp
/* Hook declarations. */
PicoTestAssertAfterProc afterAssert;
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_AFTER afterAssert

/* Hook function. */
void afterAssert(const char *type, const char *test, int fail) {
    indent(--level);
    printf("after assertion %s(%s) => %s\n", type, test, fail ? "fails" : "passes");
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_ASSERT\_AFTER](picotest_8h.md#group__assertions_1gae6c0c62e54611c6d92a3a8b81545f934)



**Return type**: void

<a id="group__assertions_1ga331ef495337f7e2aae8be15cfd2a170a"></a>
### Macro PICOTEST\_ASSERT\_BEFORE\_DEFAULT

![][public]

```cpp
#define PICOTEST_ASSERT_BEFORE_DEFAULT( type ,test )
```

Default assert before hook.

Does nothing.








**See also**: [PicoTestAssertBeforeProc](picotest_8h.md#group__assertions_1ga507d93a48b3c01ec9c43499d129d6db0), [PICOTEST\_ASSERT\_BEFORE](picotest_8h.md#group__assertions_1gaa38b1a0014fe2ab172a5466f9031aafb)



<a id="group__assertions_1gaa38b1a0014fe2ab172a5466f9031aafb"></a>
### Macro PICOTEST\_ASSERT\_BEFORE

![][public]

```cpp
#define PICOTEST_ASSERT_BEFORE
```

Define the assert before hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestAssertBeforeProc](picotest_8h.md#group__assertions_1ga507d93a48b3c01ec9c43499d129d6db0) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:

```cpp
/* Hook declarations. */
PicoTestAssertBeforeProc beforeAssert;
#undef PICOTEST_ASSERT_BEFORE
#define PICOTEST_ASSERT_BEFORE beforeAssert

/* Hook function. */
void beforeAssert(const char *type, const char *test) {
    indent(level++);
    printf("before assertion %s(%s)...\n", type, test);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestAssertBeforeProc](picotest_8h.md#group__assertions_1ga507d93a48b3c01ec9c43499d129d6db0), [PICOTEST\_ASSERT\_BEFORE\_DEFAULT](picotest_8h.md#group__assertions_1ga331ef495337f7e2aae8be15cfd2a170a), [PICOTEST\_ASSERT\_AFTER](picotest_8h.md#group__assertions_1gae6c0c62e54611c6d92a3a8b81545f934)



<a id="group__assertions_1gab1f1711109e4a8443a61c228194a6825"></a>
### Macro PICOTEST\_ASSERT\_AFTER\_DEFAULT

![][public]

```cpp
#define PICOTEST_ASSERT_AFTER_DEFAULT( type ,test ,fail )
```

Default assert after hook.

Does nothing.








**See also**: [PicoTestAssertAfterProc](picotest_8h.md#group__assertions_1ga8f5650aa00db35bc50511fa2a01a45e7), [PICOTEST\_ASSERT\_AFTER](picotest_8h.md#group__assertions_1gae6c0c62e54611c6d92a3a8b81545f934)



<a id="group__assertions_1gae6c0c62e54611c6d92a3a8b81545f934"></a>
### Macro PICOTEST\_ASSERT\_AFTER

![][public]

```cpp
#define PICOTEST_ASSERT_AFTER
```

Define the assert after hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestAssertAfterProc](picotest_8h.md#group__assertions_1ga8f5650aa00db35bc50511fa2a01a45e7) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:

```cpp
/* Hook declarations. */
PicoTestAssertAfterProc afterAssert;
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_AFTER afterAssert

/* Hook function. */
void afterAssert(const char *type, const char *test, int fail) {
    indent(--level);
    printf("after assertion %s(%s) => %s\n", type, test, fail ? "fails" : "passes");
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestAssertAfterProc](picotest_8h.md#group__assertions_1ga8f5650aa00db35bc50511fa2a01a45e7), [PICOTEST\_ASSERT\_AFTER\_DEFAULT](picotest_8h.md#group__assertions_1gab1f1711109e4a8443a61c228194a6825), [PICOTEST\_ASSERT\_BEFORE](picotest_8h.md#group__assertions_1gaa38b1a0014fe2ab172a5466f9031aafb)



## Assertion Definitions

<a id="group__assertions_1ga8d7eb92ca21dfb7fe46fc2472e11f496"></a>
### Variable \_picoTest\_fail

![][private]
![][static]

**Definition**: `include/picotest.h` (line 831)

```cpp
int _picoTest_fail
```

Internal failure counter.

**See also**: [PICOTEST\_FAILURE](picotest_8h.md#group__assertions_1ga89a35f18021df570967bb707a8537f3b)



**Type**: int

<a id="group__assertions_1ga2fdb4a73b6a0abc186a27065a36db6ed"></a>
### Variable \_picoTest\_failureEnv

![][private]
![][static]

**Definition**: `include/picotest.h` (line 839)

```cpp
jmp_buf* _picoTest_failureEnv
```

Tag used by **setjmp()** and **longjmp()** to jump out of failed tests.

**See also**: [PICOTEST\_ABORT](picotest_8h.md#group__assertions_1ga62031fa5f6f86e517565b77a1fa37f59), [PICOTEST\_CASE](picotest_8h.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



**Type**: jmp_buf *

<a id="group__assertions_1gadd80bff454009ce1077d81f1f5552f34"></a>
### Function \_picoTest\_assertFailed

![][private]
![][static]

```cpp
static void _picoTest_assertFailed(PicoTestFailureLoggerProc *proc, const char *file, int line, const char *type, int count, const char *test,...)
```

Called when an assertion fails.

**Parameters**:

* **proc**: Test failure log handler.
* **file**: File name where the test was defined.
* **line**: Location of test in file.
* **type**: Type of test that failed (e.g. "ASSERT").
* **count**: Number of arguments after **test**.
* **test**: Tested expression.
* **...**: Optional message format string and parameters.




**See also**: [PICOTEST\_ASSERT](picotest_8h.md#group__assertions_1gad71b76cf1173654acc95df79d1c7040b), [PICOTEST\_VERIFY](picotest_8h.md#group__assertions_1gacd07b017f38d1e3ad784f369345357a2)



**Parameters**:

* [PicoTestFailureLoggerProc](picotest_8h.md#group__public__interface_1gafc6530e30c90b9f92367ef643c8f4e00) * **proc**
* const char * **file**
* int **line**
* const char * **type**
* int **count**
* const char * **test**
* ...

**Return type**: void

<a id="group__assertions_1gad71b76cf1173654acc95df79d1c7040b"></a>
### Macro PICOTEST\_ASSERT

![][public]

```cpp
#define PICOTEST_ASSERT( x ,... )
```

Hard assertion.

Logs an error if the given value is false, then stops the test with [PICOTEST\_ABORT()](picotest_8h.md#group__assertions_1ga62031fa5f6f86e517565b77a1fa37f59).





[PICOTEST\_FAILURE\_LOGGER()](picotest_8h.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48) is called with the **type** argument set to <code>"ASSERT"</code>.






**Parameters**:

* **x**: Value to test. Evaluated once, so it can be an expression with side effects.
* **msg**: (optional) Message format string.
* **...**: (optional) Message string arguments.


?> **msg** and following arguments arguments are suitable arguments to **printf()**.


**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>





**See also**: [PICOTEST\_FAILURE\_LOGGER](picotest_8h.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48), [PICOTEST\_ABORT](picotest_8h.md#group__assertions_1ga62031fa5f6f86e517565b77a1fa37f59), [PICOTEST\_VERIFY](picotest_8h.md#group__assertions_1gacd07b017f38d1e3ad784f369345357a2)



<a id="group__assertions_1gacd07b017f38d1e3ad784f369345357a2"></a>
### Macro PICOTEST\_VERIFY

![][public]

```cpp
#define PICOTEST_VERIFY( x ,... )
```

Soft assertion.

Logs an error if the given value is false, but let the test continue.





[PICOTEST\_FAILURE\_LOGGER()](picotest_8h.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48) is called with the **type** argument set to <code>"VERIFY"</code>.






**Parameters**:

* **x**: Value to test. Evaluated once, so it can be an expression with side effects.
* **msg**: (optional) Message format string.
* **...**: (optional) Message string arguments.


?> **msg** and following arguments arguments are suitable arguments to **printf()**.


**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>




**See also**: [PICOTEST\_FAILURE\_LOGGER](picotest_8h.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48), [PICOTEST\_ASSERT](picotest_8h.md#group__assertions_1gad71b76cf1173654acc95df79d1c7040b)



<a id="group__assertions_1ga89a35f18021df570967bb707a8537f3b"></a>
### Macro PICOTEST\_FAILURE

![][public]

```cpp
#define PICOTEST_FAILURE( type ,test ,... )
```

Generic failure.

[PICOTEST\_FAILURE\_LOGGER()](picotest_8h.md#group__public__interface_1gae4b2f943bef59bd05fb7a328a6c39d48) is called with the provided **type**, **test** and **msg** arguments.





This can be used to implement custom testing logic.






**Parameters**:

* **type**: Type of test that failed (e.g. "ASSERT").
* **test**: Failed test.
* **msg**: (optional) Message format string.
* **...**: (optional) Message string arguments.



<a id="group__assertions_1ga62031fa5f6f86e517565b77a1fa37f59"></a>
### Macro PICOTEST\_ABORT

![][public]

```cpp
#define PICOTEST_ABORT(  )
```

Abort a test case.

This can be used to implement custom testing logic.







**See also**: [PICOTEST\_CASE](picotest_8h.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)
[private]: https://img.shields.io/badge/-private-red (private)
[static]: https://img.shields.io/badge/-static-lightgrey (static)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)