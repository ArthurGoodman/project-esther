#include "false.h"

#include "esther.h"

False::False(Esther *esther)
    : Object(esther->getRootClass("Boolean")) {
}

std::string False::toString() const {
    return "false";
}

bool False::isTrue() const {
    return false;
}
