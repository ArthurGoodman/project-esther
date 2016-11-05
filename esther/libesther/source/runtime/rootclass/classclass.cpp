#include "classclass.h"

#include "class.h"

Object *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass);
}

void ClassClass::setupMethods() {
}
