#pragma once

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
    std::string toString() const;
};
