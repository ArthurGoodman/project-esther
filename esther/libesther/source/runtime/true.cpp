#include "true.h"

#include "esther.h"

True::True(Esther *esther)
    : Object(esther->getRootClass("Boolean")) {
}

std::string True::toString() const {
    return "true";
}

void True::copy(ManagedObject *dst) {
    new (dst) True(*this);
}
