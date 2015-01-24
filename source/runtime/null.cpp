#include "null.h"

namespace esther {

Null::Null()
    : Object("NullClass") {
}

bool Null::isTrue() {
    return false;
}

bool Null::isFalse() {
    return true;
}

bool Null::isNull() {
    return true;
}

string Null::toString() {
    return "null";
}
}
