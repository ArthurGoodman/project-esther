#include "true.h"

std::string True::toString() const {
    return "true";
}

void True::copy(ManagedObject *dst) {
    new (dst) True(*this);
}

True::True(Pointer<Class> objectClass)
    : Object(objectClass) {
}
