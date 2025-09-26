<a id="group__fixtures"></a>
# Test Fixtures



Test fixtures are used to establish the context needed to run test cases.





A test fixture can be used by several, possibly unrelated test cases.

## Test Fixture Hooks

PicoTest provides a way for client code to intercept test fixture events. This can be used for e.g. logging purpose or reporting.

<a id="group__fixtures_1ga8aa61845d5a3f09e8d6df140a31c36d7"></a>
### Typedef PicoTestFixtureBeforeSetupProc

![][public]

**Definition**: `include/picotest.h` (line 1254)


```cpp
typedef void PicoTestFixtureBeforeSetupProc(const char *fixtureName, const char *testName)
```


Function signature of test fixture before setup hooks.

Called before running the test fixture setup.






**Parameters**:

* **fixtureName**: Test fixture name.
* **testName**: Test case name.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureBeforeSetupProc beforeSetup;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#define PICOTEST_FIXTURE_BEFORE_SETUP beforeSetup

/* Hook function. */
void beforeSetup(const char *fixtureName, const char *testName) {
    indent(level++);
    printf("fixture %s setup...", fixtureName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_FIXTURE\_BEFORE\_SETUP](group__fixtures.md#group__fixtures_1gab6053367243af2ee7745bf35a3baaa4e)



**Return type**: void

<a id="group__fixtures_1ga0e4c1719160ac09c22d3b4ce06704962"></a>
### Typedef PicoTestFixtureAfterSetupProc

![][public]

**Definition**: `include/picotest.h` (line 1303)


```cpp
typedef void PicoTestFixtureAfterSetupProc(const char *fixtureName, const char *testName)
```


Function signature of test fixture after setup hooks.

Called after running the test fixture setup.






**Parameters**:

* **fixtureName**: Test fixture name.
* **testName**: Test case name.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureAfterSetupProc afterSetup;
#undef PICOTEST_FIXTURE_AFTER_SETUP
#define PICOTEST_FIXTURE_AFTER_SETUP afterSetup

/* Hook function. */
void afterSetup(const char *fixtureName, const char *testName) {
    printf(" done\n");
    --level;
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_FIXTURE\_AFTER\_SETUP](group__fixtures.md#group__fixtures_1ga679063021accc32a74c1e617ed68423f)



**Return type**: void

<a id="group__fixtures_1gaf69eeeb219ed143a9a978d49850cb072"></a>
### Typedef PicoTestFixtureBeforeTeardownProc

![][public]

**Definition**: `include/picotest.h` (line 1353)


```cpp
typedef void PicoTestFixtureBeforeTeardownProc(const char *fixtureName, const char *testName, int fail)
```


Function signature of test fixture before teardown hooks.

Called before running the test fixture teardown.






**Parameters**:

* **fixtureName**: Test fixture name.
* **testName**: Test case name.
* **fail**: Failed tests (including its subtests if any).


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureBeforeTeardownProc beforeTeardown;
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN beforeTeardown

/* Hook function. */
void beforeTeardown(const char *fixtureName, const char *testName, int fail) {
    indent(level++);
    printf("fixture %s teardown...", fixtureName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN](group__fixtures.md#group__fixtures_1gaf68cbda0bf19afd7994c2e0a15278f8d)



**Return type**: void

<a id="group__fixtures_1gaf955a2ec76f0278eac70de7315ecb844"></a>
### Typedef PicoTestFixtureAfterTeardownProc

![][public]

**Definition**: `include/picotest.h` (line 1404)


```cpp
typedef void PicoTestFixtureAfterTeardownProc(const char *fixtureName, const char *testName, int fail)
```


Function signature of test fixture after teardown hooks.

Called after running the test fixture teardown.






**Parameters**:

* **fixtureName**: Test fixture name.
* **testName**: Test case name.
* **fail**: Failed tests (including its subtests if any).


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureAfterTeardownProc afterTeardown;
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_AFTER_TEARDOWN afterTeardown

/* Hook function. */
void afterTeardown(const char *fixtureName, const char *testName, int fail) {
    printf(" done\n");
    --level;
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>



**See also**: [PICOTEST\_FIXTURE\_AFTER\_TEARDOWN](group__fixtures.md#group__fixtures_1ga1a910236e326a942bc3a5be5c6013520)



**Return type**: void

<a id="group__fixtures_1ga503733d3013e81575c72a1100437ccf0"></a>
### Macro PICOTEST\_FIXTURE\_BEFORE\_SETUP\_DEFAULT

![][public]


```cpp
#define PICOTEST_FIXTURE_BEFORE_SETUP_DEFAULT( fixtureName ,testName )
```


Default test fixture before setup hook.

Does nothing.








**See also**: [PicoTestFixtureBeforeSetupProc](group__fixtures.md#group__fixtures_1ga8aa61845d5a3f09e8d6df140a31c36d7), [PICOTEST\_FIXTURE\_BEFORE\_SETUP](group__fixtures.md#group__fixtures_1gab6053367243af2ee7745bf35a3baaa4e)



<a id="group__fixtures_1gab6053367243af2ee7745bf35a3baaa4e"></a>
### Macro PICOTEST\_FIXTURE\_BEFORE\_SETUP

![][public]


```cpp
#define PICOTEST_FIXTURE_BEFORE_SETUP
```


Define the test fixture before setup hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestFixtureBeforeSetupProc](group__fixtures.md#group__fixtures_1ga8aa61845d5a3f09e8d6df140a31c36d7) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureBeforeSetupProc beforeSetup;
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#define PICOTEST_FIXTURE_BEFORE_SETUP beforeSetup

/* Hook function. */
void beforeSetup(const char *fixtureName, const char *testName) {
    indent(level++);
    printf("fixture %s setup...", fixtureName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestFixtureBeforeSetupProc](group__fixtures.md#group__fixtures_1ga8aa61845d5a3f09e8d6df140a31c36d7), [PICOTEST\_FIXTURE\_BEFORE\_SETUP\_DEFAULT](group__fixtures.md#group__fixtures_1ga503733d3013e81575c72a1100437ccf0), [PICOTEST\_FIXTURE\_AFTER\_SETUP](group__fixtures.md#group__fixtures_1ga679063021accc32a74c1e617ed68423f)



<a id="group__fixtures_1ga8bfe212f7c3bed6d83be102510086012"></a>
### Macro PICOTEST\_FIXTURE\_AFTER\_SETUP\_DEFAULT

![][public]


```cpp
#define PICOTEST_FIXTURE_AFTER_SETUP_DEFAULT( fixtureName ,testName )
```


Default test fixture after setup hook.

Does nothing.








**See also**: [PicoTestFixtureAfterSetupProc](group__fixtures.md#group__fixtures_1ga0e4c1719160ac09c22d3b4ce06704962), [PICOTEST\_FIXTURE\_AFTER\_SETUP](group__fixtures.md#group__fixtures_1ga679063021accc32a74c1e617ed68423f)



<a id="group__fixtures_1ga679063021accc32a74c1e617ed68423f"></a>
### Macro PICOTEST\_FIXTURE\_AFTER\_SETUP

![][public]


```cpp
#define PICOTEST_FIXTURE_AFTER_SETUP
```


Define the test fixture after setup hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestFixtureAfterSetupProc](group__fixtures.md#group__fixtures_1ga0e4c1719160ac09c22d3b4ce06704962) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureAfterSetupProc afterSetup;
#undef PICOTEST_FIXTURE_AFTER_SETUP
#define PICOTEST_FIXTURE_AFTER_SETUP afterSetup

/* Hook function. */
void afterSetup(const char *fixtureName, const char *testName) {
    printf(" done\n");
    --level;
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestFixtureAfterSetupProc](group__fixtures.md#group__fixtures_1ga0e4c1719160ac09c22d3b4ce06704962), [PICOTEST\_FIXTURE\_AFTER\_SETUP\_DEFAULT](group__fixtures.md#group__fixtures_1ga8bfe212f7c3bed6d83be102510086012), [PICOTEST\_FIXTURE\_BEFORE\_SETUP](group__fixtures.md#group__fixtures_1gab6053367243af2ee7745bf35a3baaa4e)



<a id="group__fixtures_1ga11bbe6bcd529ac78264411add1275635"></a>
### Macro PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN\_DEFAULT

![][public]


```cpp
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN_DEFAULT( fixtureName ,testName ,fail )
```


Default test fixture before teardown hook.

Does nothing.








**See also**: [PicoTestFixtureBeforeTeardownProc](group__fixtures.md#group__fixtures_1gaf69eeeb219ed143a9a978d49850cb072), [PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN](group__fixtures.md#group__fixtures_1gaf68cbda0bf19afd7994c2e0a15278f8d)



<a id="group__fixtures_1gaf68cbda0bf19afd7994c2e0a15278f8d"></a>
### Macro PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN

![][public]


```cpp
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN
```


Define the test fixture before teardown hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestFixtureBeforeTeardownProc](group__fixtures.md#group__fixtures_1gaf69eeeb219ed143a9a978d49850cb072) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureBeforeTeardownProc beforeTeardown;
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN beforeTeardown

/* Hook function. */
void beforeTeardown(const char *fixtureName, const char *testName, int fail) {
    indent(level++);
    printf("fixture %s teardown...", fixtureName);
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestFixtureBeforeTeardownProc](group__fixtures.md#group__fixtures_1gaf69eeeb219ed143a9a978d49850cb072), [PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN\_DEFAULT](group__fixtures.md#group__fixtures_1ga11bbe6bcd529ac78264411add1275635), [PICOTEST\_FIXTURE\_AFTER\_TEARDOWN](group__fixtures.md#group__fixtures_1ga1a910236e326a942bc3a5be5c6013520)



<a id="group__fixtures_1ga667b954d1448d95e022451b8711e6abf"></a>
### Macro PICOTEST\_FIXTURE\_AFTER\_TEARDOWN\_DEFAULT

![][public]


```cpp
#define PICOTEST_FIXTURE_AFTER_TEARDOWN_DEFAULT( fixtureName ,testName ,fail )
```


Default test fixture after teardown hook.

Does nothing.








**See also**: [PicoTestFixtureAfterTeardownProc](group__fixtures.md#group__fixtures_1gaf955a2ec76f0278eac70de7315ecb844), [PICOTEST\_FIXTURE\_AFTER\_TEARDOWN](group__fixtures.md#group__fixtures_1ga1a910236e326a942bc3a5be5c6013520)



<a id="group__fixtures_1ga1a910236e326a942bc3a5be5c6013520"></a>
### Macro PICOTEST\_FIXTURE\_AFTER\_TEARDOWN

![][public]


```cpp
#define PICOTEST_FIXTURE_AFTER_TEARDOWN
```


Define the test fixture after teardown hook.

The default hook does nothing. Redefine this macro to use a custom hook, which must follow the [PicoTestFixtureAfterTeardownProc](group__fixtures.md#group__fixtures_1gaf955a2ec76f0278eac70de7315ecb844) signature.






?> Custom functions only apply to the tests defined after the macro redefinition. As macros can be redefined several times, this means that different functions may apply for the same source.


**Usage**:


```cpp
/* Hook declarations. */
PicoTestFixtureAfterTeardownProc afterTeardown;
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_AFTER_TEARDOWN afterTeardown

/* Hook function. */
void afterTeardown(const char *fixtureName, const char *testName, int fail) {
    printf(" done\n");
    --level;
}
```


**Examples**:

[hooks.c](hooks_8c.md#hooks_8c)   Example of PicoTest hooks, prints all events to stdout.    <br/>





**See also**: [PicoTestFixtureAfterTeardownProc](group__fixtures.md#group__fixtures_1gaf955a2ec76f0278eac70de7315ecb844), [PICOTEST\_FIXTURE\_AFTER\_TEARDOWN\_DEFAULT](group__fixtures.md#group__fixtures_1ga667b954d1448d95e022451b8711e6abf), [PICOTEST\_FIXTURE\_BEFORE\_TEARDOWN](group__fixtures.md#group__fixtures_1gaf68cbda0bf19afd7994c2e0a15278f8d)



## Test Fixture Definitions

<a id="group__fixtures_1ga983cffc937dca4baa55f59afad404f03"></a>
### Macro PICOTEST\_FIXTURE\_CONTEXT

![][public]


```cpp
#define PICOTEST_FIXTURE_CONTEXT( _fixtureName )
```


Test fixture context declaration.

Fixtures can optionally define a context structure that is passed to its setup and teardown functions.






**Parameters**:

* **_fixtureName**: Name of the fixture.


**Usage**:


```cpp
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};
```


**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>
 [fixtures.c](fixtures_8c.md#fixtures_8c)   Demonstrates test fixture call sequences.    <br/>





**See also**: [PICOTEST\_FIXTURE\_SETUP](group__fixtures.md#group__fixtures_1ga1e98cba23391e13521100528ee1a2181), [PICOTEST\_FIXTURE\_TEARDOWN](group__fixtures.md#group__fixtures_1ga0d887bdb08e22489fc3cf9fb28a35fd1), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



<a id="group__fixtures_1ga1e98cba23391e13521100528ee1a2181"></a>
### Macro PICOTEST\_FIXTURE\_SETUP

![][public]


```cpp
#define PICOTEST_FIXTURE_SETUP( ... )
```


Test fixture initialization.

**Parameters**:

* **_fixtureName**: Name of the fixture.
* **_context**: (optional) Fixture context structure defined using [PICOTEST\_FIXTURE\_CONTEXT(\_fixtureName)](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03).


**Usage**:

A simple fixture with no context: 
```cpp
/* Simple fixture */
PICOTEST_FIXTURE_SETUP(simpleFixture) {
    /* Initialize static stuff */
    staticVar = 1;
    srand(1234);
}
PICOTEST_FIXTURE_TEARDOWN(simpleFixture) {
    /* Cleanup static stuff */
    staticVar = 0;
    srand(clock());
}
```

A more complex example with a context structure: 
```cpp
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithContext, context) {
    /* Initialize static stuff */
    staticVar = 2;

    /* Initialize fixture context */
    context->var1 = 1;
    context->var2 = "test";
    context->var3 = (void *) malloc(1);
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    free(context->var3);
}
```






Fixtures may define an optional context that test cases don't need, in this case the context passed to the setup and teardown functions is **NULL**: 
```cpp
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithOptionalContext) {
    void *buffer;
};

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithOptionalContext, context) {
    /* Initialize static stuff */
    staticVar = 3;

    /* Initialize fixture context */
    if (context) {
        staticVar++;
        context->buffer = (void *) malloc(1);
    }
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithOptionalContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    if (context) {
        free(context->buffer);
    }
}
```
 Here is an example of such a test case: 
```cpp
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}
```







**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>
 [fixtures.c](fixtures_8c.md#fixtures_8c)   Demonstrates test fixture call sequences.    <br/>





**See also**: [PICOTEST\_FIXTURE\_CONTEXT](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03), [PICOTEST\_FIXTURE\_TEARDOWN](group__fixtures.md#group__fixtures_1ga0d887bdb08e22489fc3cf9fb28a35fd1), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



<a id="group__fixtures_1ga0d887bdb08e22489fc3cf9fb28a35fd1"></a>
### Macro PICOTEST\_FIXTURE\_TEARDOWN

![][public]


```cpp
#define PICOTEST_FIXTURE_TEARDOWN( ... )
```


Test fixture cleanup.

**Parameters**:

* **_fixtureName**: Name of the fixture.
* **_context**: (optional) Fixture context structure defined using [PICOTEST\_FIXTURE\_CONTEXT(\_fixtureName)](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03).


**Usage**:

A simple fixture with no context: 
```cpp
/* Simple fixture */
PICOTEST_FIXTURE_SETUP(simpleFixture) {
    /* Initialize static stuff */
    staticVar = 1;
    srand(1234);
}
PICOTEST_FIXTURE_TEARDOWN(simpleFixture) {
    /* Cleanup static stuff */
    staticVar = 0;
    srand(clock());
}
```

A more complex example with a context structure: 
```cpp
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithContext) {
    int var1;
    const char *var2;
    void *var3;
};

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithContext, context) {
    /* Initialize static stuff */
    staticVar = 2;

    /* Initialize fixture context */
    context->var1 = 1;
    context->var2 = "test";
    context->var3 = (void *) malloc(1);
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    free(context->var3);
}
```






Fixtures may define an optional context that test cases don't need, in this case the context passed to the setup and teardown functions is **NULL**: 
```cpp
/* Fixture context */
PICOTEST_FIXTURE_CONTEXT(fixtureWithOptionalContext) {
    void *buffer;
};

/* Fixture setup */
PICOTEST_FIXTURE_SETUP(fixtureWithOptionalContext, context) {
    /* Initialize static stuff */
    staticVar = 3;

    /* Initialize fixture context */
    if (context) {
        staticVar++;
        context->buffer = (void *) malloc(1);
    }
}

/* Fixture teardown */
PICOTEST_FIXTURE_TEARDOWN(fixtureWithOptionalContext, context) {
    /* Cleanup static stuff */
    staticVar = 0;

    /* Cleanup fixture context */
    if (context) {
        free(context->buffer);
    }
}
```
 Here is an example of such a test case: 
```cpp
PICOTEST_CASE(testCase5, fixtureWithOptionalContext) {
    PICOTEST_VERIFY(staticVar == 3);    /* Passes */
    PICOTEST_ASSERT(PASSES);            /* Passes */
}
```







**Examples**:

[mainSuite.inc](main_suite_8inc.md#main_suite_8inc)   Example of a simple PicoTest suite.    <br/>
 [fixtures.c](fixtures_8c.md#fixtures_8c)   Demonstrates test fixture call sequences.    <br/>





**See also**: [PICOTEST\_FIXTURE\_CONTEXT](group__fixtures.md#group__fixtures_1ga983cffc937dca4baa55f59afad404f03), [PICOTEST\_FIXTURE\_SETUP](group__fixtures.md#group__fixtures_1ga1e98cba23391e13521100528ee1a2181), [PICOTEST\_CASE](group__test__cases.md#group__test__cases_1gadca8898d29eb42dde764ed83a5d9faf5)



[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)
[public]: https://img.shields.io/badge/-public-brightgreen (public)
[Markdown]: https://img.shields.io/badge/language-Markdown-blue (Markdown)