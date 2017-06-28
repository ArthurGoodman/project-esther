#include "esther/common.h"

#include "esther/id.h"

bool string_compare(void *a, void *b) {
    return strcmp(a, b) < 0;
}

bool id_compare(void *a, void *b) {
    return (Id)a < (Id)b;
}
