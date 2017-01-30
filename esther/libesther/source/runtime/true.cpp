#include "true.h"

std::string True::toString() const {
    return "true";
}

True::True(Pointer<Class> objectClass)
    : Object(objectClass) {
}
