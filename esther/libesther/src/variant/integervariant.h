#pragma once

#include "common/common.h"

#if HEAP_VARIANT

#include "variant/variantprivate.h"

class IntegerVariant : public VariantPrivate {
    int value;

public:
    IntegerVariant(int value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;
};

#endif
