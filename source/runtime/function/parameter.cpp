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

bool Parameter::equals(Object *other) {
    if (!dynamic_cast<Parameter *>(other))
        return false;

    return type->equals(((Parameter *)other)->type) && (value ? value->equals(((Parameter *)other)->value) : true);
}
