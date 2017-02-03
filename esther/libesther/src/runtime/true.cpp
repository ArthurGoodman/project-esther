#include "runtime/true.h"

#include "esther.h"

namespace es {

True::True(Esther *esther)
    : Object(esther->getRootClass("Boolean")) {
}

std::string True::toString() const {
    return "true";
}
}
