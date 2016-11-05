#pragma once

#include "object.h"
#include "variant.h"

class Runtime;

class ValueObject : public Object {
    friend class IntegerClass;
    friend class FloatClass;
    friend class CharacterClass;
    friend class StringClass;

    Variant value;

public:
    static Object *createNewInstance(Runtime *runtime, const Variant &value);

    Variant getVariant();

    std::string toString() const;

private:
    ValueObject(Class *objectClass, const Variant &value);
};
