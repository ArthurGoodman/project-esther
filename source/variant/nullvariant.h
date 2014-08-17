#pragma once
#include <common.h>

#include "variantprivate.h"

class NullVariant : public VariantPrivate
{
public:
    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    string toString() const;
};
