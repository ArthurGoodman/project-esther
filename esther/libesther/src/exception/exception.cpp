#include "exception/exception.h"

namespace es {

Exception::~Exception() {
}

std::string Exception::message() {
    return "";
}
}
