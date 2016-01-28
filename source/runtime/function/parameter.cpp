#include "parameter.h"

#include "class.h"

Parameter::Parameter(Class *type, string name, IObject *value)
    : type(type), name(name), value(value) {
}

Class *Parameter::getType() {
    return type;
}

string Parameter::getName() {
    return name;
}

IObject *Parameter::getValue() {
    return value;
}

bool Parameter::equals(Parameter *other) {
    return type == other->type && ((value && other->value) ? value->callEquals(other->value) : (value == other->value));
}

IObject *Parameter::clone() {
    return new Parameter(type, name, value);
}
