#include "class.h"

std::string Class::getName() const {
    return name;
}

void Class::setName(const std::string &name) {
    this->name = name;
}

Object *Class::newInstance() {
    return createNewInstance();
}

Object *Class::createNewInstance() {
    return new Object(this);
}
