#pragma once
#include "common.h"

#include "object.h"
#include "variant.h"

class ValueObject : public Object {
protected:
    Variant value;

public:
    ValueObject(int value);
    ValueObject(double value);
    ValueObject(char value);
    ValueObject(string value);
    ValueObject(const Variant &value);

    Variant getVariant();

    string toString();

protected:
    void setVariant(Variant value);

private:
    static string typeToClassName(Variant::Type type);
};
