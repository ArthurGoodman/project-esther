#pragma once

#include "object.h"
#include "variant.h"

class ValueObject : public Object {
protected:
    Variant value;

public:
    static ValueObject *createNewInstance(const Variant &value);

    ValueObject(int value);
    ValueObject(double value);
    ValueObject(char value);
    ValueObject(const std::string &value);
    ValueObject(const Variant &value);

    Variant getVariant();

    IObject *clone();

protected:
    void setVariant(Variant value);

private:
    static std::string typeToClassName(Variant::Type type);
};
