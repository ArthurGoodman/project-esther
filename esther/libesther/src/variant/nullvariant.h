#pragma once

#include "common/config.h"

#if HEAP_VARIANT

#include "variant/variantprivate.h"

namespace es {

class NullVariant : public VariantPrivate {
public:
    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;
};
}

#endif
