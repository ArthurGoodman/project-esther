#include "esther/common.h"

#include "esther/id.h"
#include "esther/object.h"
#include "esther/std_string.h"

bool compare_str(void *a, void *b) {
    return string_compare(*(struct string *) a, *(struct string *) b) < 0;
}

bool compare_id(void *a, void *b) {
    return (ID) a < (ID) b;
}

bool compare_obj(void *a, void *b) {
    return Object_less(a, b);
}
