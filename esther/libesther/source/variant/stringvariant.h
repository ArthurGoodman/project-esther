#pragma once

#include "common.h"

#if HEAP_VARIANT

#include "variantprivate.h"

class StringVariant : public VariantPrivate {
    std::string value;

public:
    StringVariant(const std::string &value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;
};

#endif
