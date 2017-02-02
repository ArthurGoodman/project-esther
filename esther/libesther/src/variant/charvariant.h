#pragma once

#include "common/common.h"

#if HEAP_VARIANT

#include "variant/variantprivate.h"

class CharVariant : public VariantPrivate {
    char value;

public:
    CharVariant(char value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;
};

#endif
