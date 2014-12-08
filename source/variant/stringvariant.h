#pragma once
#include <common.h>

#include "variantprivate.h"

class StringVariant : public VariantPrivate {
    string value;

public:
    StringVariant(string value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    string toString() const;
};
