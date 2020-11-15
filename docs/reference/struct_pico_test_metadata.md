<a id="struct_pico_test_metadata"></a>
# Structure PicoTestMetadata

![][C++]
![][public]

**Definition**: `include/picotest.h` (line 109)

Test metadata.



## Members

* [file](struct_pico_test_metadata.md#struct_pico_test_metadata_1a1e57db62ee1f5581d0f0bca333e21304)
* [line](struct_pico_test_metadata.md#struct_pico_test_metadata_1a98c9bcbb6844cf75dd8005110b03887d)
* [name](struct_pico_test_metadata.md#struct_pico_test_metadata_1a253651ce46bc33b206c12787e8ccb166)
* [nbSubtests](struct_pico_test_metadata.md#struct_pico_test_metadata_1a7dd93cc6b50428b9594d171c28a563c1)
* [subtests](struct_pico_test_metadata.md#struct_pico_test_metadata_1a543874ce98d5f3516e4e5bda6f4e61a3)
* [test](struct_pico_test_metadata.md#struct_pico_test_metadata_1a3f209675beb238cc9a2caf31996c3388)

## Public attributes

<a id="struct_pico_test_metadata_1a253651ce46bc33b206c12787e8ccb166"></a>
### Variable name

![][public]

**Definition**: `include/picotest.h` (line 110)

```cpp
const char* PicoTestMetadata::name
```



Test name.



**Type**: const char *

<a id="struct_pico_test_metadata_1a1e57db62ee1f5581d0f0bca333e21304"></a>
### Variable file

![][public]

**Definition**: `include/picotest.h` (line 111)

```cpp
const char* PicoTestMetadata::file
```



Test file location.



**Type**: const char *

<a id="struct_pico_test_metadata_1a98c9bcbb6844cf75dd8005110b03887d"></a>
### Variable line

![][public]

**Definition**: `include/picotest.h` (line 112)

```cpp
int PicoTestMetadata::line
```



Test line location.



**Type**: int

<a id="struct_pico_test_metadata_1a3f209675beb238cc9a2caf31996c3388"></a>
### Variable test

![][public]

**Definition**: `include/picotest.h` (line 113)

```cpp
PicoTestProc* const PicoTestMetadata::test
```



Test function.



**Type**: [PicoTestProc](picotest_8h.md#group__public__interface_1ga824e8707dfbd1726aa15beb5f27b957a) *const

<a id="struct_pico_test_metadata_1a7dd93cc6b50428b9594d171c28a563c1"></a>
### Variable nbSubtests

![][public]

**Definition**: `include/picotest.h` (line 114)

```cpp
int PicoTestMetadata::nbSubtests
```



Number of subtests.



**Type**: int

<a id="struct_pico_test_metadata_1a543874ce98d5f3516e4e5bda6f4e61a3"></a>
### Variable subtests

![][public]

**Definition**: `include/picotest.h` (line 116)

```cpp
const struct PicoTestMetadata* * PicoTestMetadata::subtests
```



Subtests (NULL-terminated array for test suites, NULL pointer for test cases).



**Type**: const struct [PicoTestMetadata](struct_pico_test_metadata.md#struct_pico_test_metadata) **

[public]: https://img.shields.io/badge/-public-brightgreen (public)
[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)