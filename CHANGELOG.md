# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

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

- Add PICOTEST_FAILURE

### Fixed

- Fix failure count for non-abortive failures

## [1.0.0] - 2018-05-08

### Added

- First release.

[unreleased]: https://github.com/fredericbonnet/picotest/compare/v1.2.1...HEAD
[1.2.1]: https://github.com/fredericbonnet/picotest/compare/v1.2.0...v1.2.1
[1.2.0]: https://github.com/fredericbonnet/picotest/compare/v1.1.0...v1.2.0
[1.1.0]: https://github.com/fredericbonnet/picotest/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/fredericbonnet/picotest/releases/tag/v1.0.0
