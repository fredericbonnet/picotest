#include <stdio.h>

/* Print string in JSON format */
void printJsonString(const char *s) {
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

void printJsonIntMember(const char *key, int value) {
    printJsonString(key);
    printf(":%d", value);
}
void printJsonStringMember(const char *key, const char *value) {
    printJsonString(key);
    printf(":");
    printJsonString(value);
}
