#include <stdio.h>

#include <picotest.h>

#include "traverse.h"

/* Traversal function, will print test cases only */
void printTestCase(const char *name, int nb) {
    if (nb == 0)
        printf("%s\n", name);
}

/* Traversal function, will print all tests */
void printTestName(const char *name, int nb) {
    printf("%s\n", name);
}

/* Print string in JSON format */
static void printJsonString(const char *s) {
    putc('"', stdout);
    for (const char *c = s; *c; c++) {
        switch (*c) {
        case '\"':
            fputs("\\\"", stdout);
            break;
        case '\\':
            fputs("\\\\", stdout);
            break;
        case '\b':
            fputs("\\b", stdout);
            break;
        case '\f':
            fputs("\\f", stdout);
            break;
        case '\n':
            fputs("\\n", stdout);
            break;
        case '\r':
            fputs("\\r", stdout);
            break;
        case '\t':
            fputs("\\t", stdout);
            break;
        default:
            putc(*c, stdout);
        }
    }
    putc('"', stdout);
}

/* Visit function, will print suite in JSON format */
void printTestSuiteJson(const PicoTestMetadata *metadata,
                        PicoTestVisitStep step) {
    static int level = 0;
    static int first = 1;
    int i;

    if (step == PICOTEST_VISIT_LEAVE) {
        if (metadata->nbSubtests) {
            level--;
            printf("\n");
            for (i = 0; i < level; i++) {
                printf(" ");
            }
            printf("]");
        }
        printf("}");
        return;
    }

    if (!first) {
        printf(",\n");
    }
    first = 0;
    for (i = 0; i < level; i++) {
        printf(" ");
    }
    printf("{");

    printJsonString("name");
    printf(":");
    printJsonString(metadata->name);

    printf(",");

    printJsonString("file");
    printf(":");
    printJsonString(metadata->file);

    printf(",");
    printJsonString("line");
    printf(":%d", metadata->line);

    if (metadata->nbSubtests) {
        printf(",");

        level++;
        first = 1;
        printJsonString("subtests");
        printf(":[\n");
    }
}