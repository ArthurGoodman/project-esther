#include "true.h"

namespace esther {

True::True()
    : Object("TrueClass") {
}

bool True::isTrue() {
    return true;
}

bool True::isFalse() {
    return false;
}

bool True::isNull() {
    return false;
}

string True::toString() {
    return "true";
}
}
