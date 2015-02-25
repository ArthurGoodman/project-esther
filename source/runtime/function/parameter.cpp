#include "parameter.h"

#include "class.h"

Parameter::Parameter(Class *type, string name, Object *value)
    : type(type), name(name), value(value) {
}

Class *Parameter::getType() {
    return type;
}

string Parameter::getName() {
    return name;
}

Object *Parameter::getValue() {
    return value;
}

bool Parameter::equals(Parameter *other) {
    return type->equals(other->type) && ((value && other->value) ? value->equals(other->value) : true);
}
