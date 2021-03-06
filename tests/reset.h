/* Test filter */
#undef PICOTEST_FILTER
#define PICOTEST_FILTER PICOTEST_FILTER_DEFAULT

/* Test failure logger */
#undef PICOTEST_FAILURE_LOGGER
#define PICOTEST_FAILURE_LOGGER PICOTEST_FAILURE_LOGGER_DEFAULT

/* Test case hooks */
#undef PICOTEST_CASE_ENTER
#undef PICOTEST_CASE_LEAVE
#define PICOTEST_CASE_ENTER PICOTEST_CASE_ENTER_DEFAULT
#define PICOTEST_CASE_LEAVE PICOTEST_CASE_LEAVE_DEFAULT

/* Assertion hooks */
#undef PICOTEST_ASSERT_BEFORE
#undef PICOTEST_ASSERT_AFTER
#define PICOTEST_ASSERT_BEFORE PICOTEST_ASSERT_BEFORE_DEFAULT
#define PICOTEST_ASSERT_AFTER PICOTEST_ASSERT_AFTER_DEFAULT

/* Test fixture hooks */
#undef PICOTEST_FIXTURE_BEFORE_SETUP
#undef PICOTEST_FIXTURE_AFTER_SETUP
#undef PICOTEST_FIXTURE_BEFORE_TEARDOWN
#undef PICOTEST_FIXTURE_AFTER_TEARDOWN
#define PICOTEST_FIXTURE_BEFORE_SETUP PICOTEST_FIXTURE_BEFORE_SETUP_DEFAULT
#define PICOTEST_FIXTURE_AFTER_SETUP PICOTEST_FIXTURE_AFTER_SETUP_DEFAULT
#define PICOTEST_FIXTURE_BEFORE_TEARDOWN                                       \
    PICOTEST_FIXTURE_BEFORE_TEARDOWN_DEFAULT
#define PICOTEST_FIXTURE_AFTER_TEARDOWN PICOTEST_FIXTURE_AFTER_TEARDOWN_DEFAULT

/* Test suite hooks */
#undef PICOTEST_SUITE_ENTER
#undef PICOTEST_SUITE_LEAVE
#undef PICOTEST_SUITE_BEFORE_SUBTEST
#undef PICOTEST_SUITE_AFTER_SUBTEST
#define PICOTEST_SUITE_ENTER PICOTEST_SUITE_ENTER_DEFAULT
#define PICOTEST_SUITE_LEAVE PICOTEST_SUITE_LEAVE_DEFAULT
#define PICOTEST_SUITE_BEFORE_SUBTEST PICOTEST_SUITE_BEFORE_SUBTEST_DEFAULT
#define PICOTEST_SUITE_AFTER_SUBTEST PICOTEST_SUITE_AFTER_SUBTEST_DEFAULT
