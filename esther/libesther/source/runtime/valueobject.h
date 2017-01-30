#pragma once

#include "object.h"
#include "variant/variant.h"

class Esther;

class ValueObject : public Object {
    friend class IntegerClass;
    friend class FloatClass;
    friend class CharacterClass;
    friend class StringClass;

    Variant value;

public:
    Variant getVariant() const;
    void setVariant(const Variant &value);

    std::string toString() const;

private:
    ValueObject(Pointer<Class> objectClass, const Variant &value);
};
