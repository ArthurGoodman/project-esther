#pragma once
#include <common.h>

#include "variantprivate.h"

class CharVariant : public VariantPrivate
{
    char value;

public:
    CharVariant(char value);

    VariantPrivate *clone() const;

    Variant::Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    string toString() const;
};
