#include "runtime/null.h"

#include "esther.h"

namespace es {

Null::Null(Esther *esther)
    : Object(esther->getRootClass("Null")) {
}

std::string Null::toString() const {
    return "null";
}

bool Null::isTrue() const {
    return false;
}
}
