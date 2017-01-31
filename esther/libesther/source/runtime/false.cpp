#include "false.h"

std::string False::toString() const {
    return "false";
}

bool False::isTrue() const {
    return false;
}

void False::copy(ManagedObject *dst) {
    new (dst) False(*this);
}

False::False(Pointer<Class> objectClass)
    : Object(objectClass) {
}
