#pragma once

#include "object.h"
#include "variant.h"

class Context;

class ValueObject : public Object {
protected:
    Variant value;

public:
    static ValueObject *createNewInstance(Context *context, const Variant &value);

    Variant getVariant();

protected:
    void setVariant(Variant value);

private:
    static std::string typeToClassName(Variant::Type type);

    ValueObject(Context *context, const Variant &value);
};
