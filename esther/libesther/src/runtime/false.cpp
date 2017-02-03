#include "runtime/false.h"

#include "esther.h"

namespace es {

False::False(Esther *esther)
    : Object(esther->getRootClass("Boolean")) {
}

std::string False::toString() const {
    return "false";
}

bool False::isTrue() const {
    return false;
}
}
