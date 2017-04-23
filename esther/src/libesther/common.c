#include "esther/common.h"

bool string_compare(void *a, void *b) {
    return strcmp(a, b) < 0;
}

bool uint32_compare(void *a, void *b) {
    return (uint32_t)a < (uint32_t)b;
}
