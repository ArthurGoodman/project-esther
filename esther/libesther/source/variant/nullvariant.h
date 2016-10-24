#pragma once

#include "variantprivate.h"

class NullVariant : public VariantPrivate {
public:
    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    std::string toString() const;
};
