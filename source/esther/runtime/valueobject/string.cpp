#include "string.h"

namespace esther {

String::String(string value)
    : ValueObject(value) {
}

String::String(const char *value)
    : ValueObject(string(value)) {
}

String::String()
    : ValueObject("") {
}
}
