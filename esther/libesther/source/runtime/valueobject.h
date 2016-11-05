#pragma once

#include "object.h"
#include "variant.h"

class Context;

class ValueObject : public Object {
    friend class IntegerClass;
    friend class FloatClass;
    friend class CharacterClass;
    friend class StringClass;

    Variant value;

public:
    static Object *createNewInstance(Context *context, const Variant &value);

    Variant getVariant();

private:
    ValueObject(Class *objectClass, const Variant &value);
};
