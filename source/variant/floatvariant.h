#pragma once
#include "common.h"

#include "variantprivate.h"

class FloatVariant : public VariantPrivate {
    double value;

public:
    FloatVariant(double value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    string toString() const;
};
