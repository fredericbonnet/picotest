#include <stdio.h>

#include <picotest.h>

/*
 * Test utilities
 */

PICOTEST_SUITE(doMetadataSuite, doMetadataCase1, doMetadataSubsuite,
               doMetadataCase2);
static int doMetadataSuiteLine = __LINE__ - 1;
PICOTEST_SUITE(doMetadataSubsuite, doMetadataSubcase1, doMetadataSubcase2);
static int doMetadataSubsuiteLine = __LINE__ - 1;
PICOTEST_CASE(doMetadataCase1) {}
static int doMetadataCase1Line = __LINE__ - 1;
PICOTEST_CASE(doMetadataCase2) {}
static int doMetadataCase2Line = __LINE__ - 1;
PICOTEST_CASE(doMetadataSubcase1) {}
static int doMetadataSubcase1Line = __LINE__ - 1;
PICOTEST_CASE(doMetadataSubcase2) {}
static int doMetadataSubcase2Line = __LINE__ - 1;

/*
 * Test suite for test metadata
 */
#include "hooks.h"

PICOTEST_SUITE(testMetadata, testMetadataShouldFindItself,
               testMetadataShouldFindLocalTests,
               testMetadataShouldDeclareExternalTests,
               testMetadataShouldKnowTestName,
               testMetadataShouldKnowTestLocation,
               testMetadataShouldKnowSubtests);

PICOTEST_CASE(testMetadataShouldFindItself) {
    PicoTestMetadata *self = PICOTEST_METADATA(testMetadataShouldFindItself);
    PICOTEST_ASSERT(self != NULL);
    PICOTEST_VERIFY(self->test == testMetadataShouldFindItself);
}
PICOTEST_CASE(testMetadataShouldFindLocalTests) {
    PicoTestMetadata *metadata;

    metadata = PICOTEST_METADATA(doMetadataSuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataSuite);

    metadata = PICOTEST_METADATA(doMetadataSubsuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataSubsuite);

    metadata = PICOTEST_METADATA(doMetadataCase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataCase1);

    metadata = PICOTEST_METADATA(doMetadataCase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataCase2);

    metadata = PICOTEST_METADATA(doMetadataSubcase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataSubcase1);

    metadata = PICOTEST_METADATA(doMetadataSubcase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == doMetadataSubcase2);
}
PICOTEST_EXTERN(mainSuite);
PICOTEST_CASE(testMetadataShouldDeclareExternalTests) {
    PicoTestMetadata *metadata = PICOTEST_METADATA(mainSuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->test == mainSuite);
}
PICOTEST_CASE(testMetadataShouldKnowTestName) {
    PicoTestMetadata *metadata;

    metadata = PICOTEST_METADATA(doMetadataSuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataSuite") == 0);

    metadata = PICOTEST_METADATA(doMetadataSubsuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataSubsuite") == 0);

    metadata = PICOTEST_METADATA(doMetadataCase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataCase1") == 0);

    metadata = PICOTEST_METADATA(doMetadataCase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataCase2") == 0);

    metadata = PICOTEST_METADATA(doMetadataSubcase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataSubcase1") == 0);

    metadata = PICOTEST_METADATA(doMetadataSubcase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->name, "doMetadataSubcase2") == 0);
}
PICOTEST_CASE(testMetadataShouldKnowTestLocation) {
    PicoTestMetadata *metadata;

    metadata = PICOTEST_METADATA(doMetadataSuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataSuiteLine);

    metadata = PICOTEST_METADATA(doMetadataSubsuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataSubsuiteLine);

    metadata = PICOTEST_METADATA(doMetadataCase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataCase1Line);

    metadata = PICOTEST_METADATA(doMetadataCase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataCase2Line);

    metadata = PICOTEST_METADATA(doMetadataSubcase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataSubcase1Line);

    metadata = PICOTEST_METADATA(doMetadataSubcase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(strcmp(metadata->file, __FILE__) == 0);
    PICOTEST_VERIFY(metadata->line == doMetadataSubcase2Line);
}
PICOTEST_CASE(testMetadataShouldKnowSubtests) {
    PicoTestMetadata *metadata;

    metadata = PICOTEST_METADATA(doMetadataSuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 3);
    PICOTEST_VERIFY(metadata->subtests[0]->test == doMetadataCase1);
    PICOTEST_VERIFY(metadata->subtests[1]->test == doMetadataSubsuite);
    PICOTEST_VERIFY(metadata->subtests[2]->test == doMetadataCase2);
    PICOTEST_VERIFY(metadata->subtests[3] == NULL);

    metadata = PICOTEST_METADATA(doMetadataSubsuite);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 2);
    PICOTEST_VERIFY(metadata->subtests[0]->test == doMetadataSubcase1);
    PICOTEST_VERIFY(metadata->subtests[1]->test == doMetadataSubcase2);
    PICOTEST_VERIFY(metadata->subtests[2] == NULL);

    metadata = PICOTEST_METADATA(doMetadataCase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 0);
    PICOTEST_VERIFY(metadata->subtests == NULL);

    metadata = PICOTEST_METADATA(doMetadataCase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 0);
    PICOTEST_VERIFY(metadata->subtests == NULL);

    metadata = PICOTEST_METADATA(doMetadataSubcase1);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 0);
    PICOTEST_VERIFY(metadata->subtests == NULL);

    metadata = PICOTEST_METADATA(doMetadataSubcase2);
    PICOTEST_ASSERT(metadata != NULL);
    PICOTEST_VERIFY(metadata->nbSubtests == 0);
    PICOTEST_VERIFY(metadata->subtests == NULL);
}