#pragma once

#include "common/common.h"

#if HEAP_VARIANT

#include "variant/variantprivate.h"

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
