#pragma once

#include "common/config.h"

#ifdef HEAP_VARIANT

#include "variant/variantprivate.h"

namespace es {

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
}

#endif
