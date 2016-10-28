#pragma once

#include "common.h"

#if HEAP_VARIANT

#include "variantprivate.h"

class FloatVariant : public VariantPrivate {
    double value;

public:
    FloatVariant(double value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;
};

#endif
