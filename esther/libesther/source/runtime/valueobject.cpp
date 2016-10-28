#include "valueobject.h"

#include "context.h"
#include "runtime.h"

ValueObject *ValueObject::createNewInstance(Context *context, const Variant &value) {
    return new ValueObject(context, value);
}

Variant ValueObject::getVariant() {
    return value;
}

void ValueObject::setVariant(Variant value) {
    this->value = value;
}

std::string ValueObject::typeToClassName(Variant::Type type) {
    switch (type) {
    case Variant::Integer:
        return "Integer";
    case Variant::Real:
        return "Float";
    case Variant::Char:
        return "Character";
    case Variant::String:
        return "String";

    default:
        return "";
    }
}

ValueObject::ValueObject(Context *context, const Variant &value)
    : Object(context->getRuntime()->getRootClass(typeToClassName(value.getType()))), value(value) {
}
