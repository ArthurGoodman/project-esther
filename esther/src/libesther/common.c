#include "esther/common.h"

#include "esther/id.h"
#include "esther/std_string.h"

bool compare_str(void *a, void *b) {
    return string_compare((struct string *) &a, *((struct string *) &b)) < 0;
}

bool compare_id(void *a, void *b) {
    return (Id) a < (Id) b;
}
