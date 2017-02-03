#pragma once

#include "common/config.h"

#if HEAP_VARIANT

#include "variant/variantprivate.h"

namespace es {

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
}

#endif
