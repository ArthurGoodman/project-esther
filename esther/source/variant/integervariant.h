#pragma once

#include "variantprivate.h"

class IntegerVariant : public VariantPrivate {
    int value;

public:
    IntegerVariant(int value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    std::string toString() const;
};
