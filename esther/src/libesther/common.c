#include "esther/common.h"

#include "esther/id.h"

bool compare_strings(void *a, void *b) {
    return strcmp(a, b) < 0;
}

bool compare_ids(void *a, void *b) {
    return (Id) a < (Id) b;
}
