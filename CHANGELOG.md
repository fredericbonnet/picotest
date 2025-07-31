# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.4.3] - 2025-07-31

### Added

- Modernize CMake packaging and add Conan recipe

## [1.4.2] - 2021-08-03

### Fixed

- Fix minor clang warning

## [1.4.1] - 2020-09-01

### Fixed

- Fix extern test declaration. This should fix issue #2
- Fix minor GCC warnings

## [1.4.0] - 2020-03-12

### Added

- Add test metadata
- Add PICOTEST_VISIT for advanced test traversal scenarios

## [1.3.0] - 2020-03-06

### Added

- Add test suite
- Make default logger/filter/hooks public:

  - `PICOTEST_FILTER_DEFAULT`
  - `PICOTEST_FAILURE_LOGGER_DEFAULT`
  - `PICOTEST_CASE_ENTER_DEFAULT`
  - `PICOTEST_CASE_LEAVE_DEFAULT`
  - `PICOTEST_ASSERT_BEFORE_DEFAULT`
  - `PICOTEST_ASSERT_AFTER_DEFAULT`
  - `PICOTEST_FIXTURE_BEFORE_SETUP_DEFAULT`
  - `PICOTEST_FIXTURE_AFTER_SETUP_DEFAULT`
  - `PICOTEST_FIXTURE_BEFORE_TEARDOWN_DEFAULT`
  - `PICOTEST_FIXTURE_AFTER_TEARDOWN_DEFAULT`
  - `PICOTEST_SUITE_ENTER_DEFAULT`
  - `PICOTEST_SUITE_LEAVE_DEFAULT`
  - `PICOTEST_SUITE_BEFORE_SUBTEST_DEFAULT`
  - `PICOTEST_SUITE_AFTER_SUBTEST_DEFAULT`

## [1.2.1] - 2020-03-02

### Fixed

- Fix issues with one-liner conditional tests. For example:

  ```c
  if (some_cond) PICOTEST_ASSERT(some_test);
  ```

  This code would compile, but the assertion would be evaluated whatever the condition `some_cond`.

## [1.2.0] - 2020-01-21

### Added

- Add assertion hooks

## [1.1.0] - 2019-17-11

### Added

- Add `PICOTEST_FAILURE`

### Fixed

- Fix failure count for non-abortive failures

## [1.0.0] - 2018-05-08

### Added

- First release.

[unreleased]: https://github.com/fredericbonnet/picotest/compare/v1.4.3...HEAD
[1.4.3]: https://github.com/fredericbonnet/picotest/compare/v1.4.2...v1.4.3
[1.4.2]: https://github.com/fredericbonnet/picotest/compare/v1.4.1...v1.4.2
[1.4.1]: https://github.com/fredericbonnet/picotest/compare/v1.4.0...v1.4.1
[1.4.0]: https://github.com/fredericbonnet/picotest/compare/v1.3.0...v1.4.0
[1.3.0]: https://github.com/fredericbonnet/picotest/compare/v1.2.1...v1.3.0
[1.2.1]: https://github.com/fredericbonnet/picotest/compare/v1.2.0...v1.2.1
[1.2.0]: https://github.com/fredericbonnet/picotest/compare/v1.1.0...v1.2.0
[1.1.0]: https://github.com/fredericbonnet/picotest/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/fredericbonnet/picotest/releases/tag/v1.0.0
