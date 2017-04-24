#include "esther/common.h"

bool string_compare(void *a, void *b) {
    return strcmp(a, b) < 0;
}

bool ulong_compare(void *a, void *b) {
    return (unsigned long int)a < (unsigned long int)b;
}
