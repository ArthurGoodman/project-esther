#include "null.h"

std::string Null::toString() const {
    return "null";
}

bool Null::isTrue() const {
    return false;
}

void Null::copy(ManagedObject *dst) {
    new (dst) Null(*this);
}

Null::Null(Pointer<Class> objectClass)
    : Object(objectClass) {
}
