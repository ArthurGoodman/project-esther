#pragma once

#include "runtime/object.h"
#include "variant/variant.h"

class Esther;

class ValueObject : public Object {
    Variant value;

public:
    ValueObject(Esther *esther, const Variant &value);

    Variant getVariant() const;
    void setVariant(const Variant &value);

    std::string toString() const override;

    void finalize() override;
    int getSize() const override;

private:
    static Ptr<Class> variantTypeToObjectClass(Esther *esther, Variant::Type type);
};
