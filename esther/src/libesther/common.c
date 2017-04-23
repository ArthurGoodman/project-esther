#include "esther/common.h"

bool string_compare(void *a, void *b) {
    return strcmp(a, b) < 0;
}
