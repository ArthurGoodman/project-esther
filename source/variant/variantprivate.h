#pragma once
#include <common.h>

#include "variant.h"

class VariantPrivate {
    friend class Variant;

public:
    virtual ~VariantPrivate();

private:
    virtual VariantPrivate *clone() const = 0;

    virtual Variant::Type type() const = 0;

    virtual int toInteger() const = 0;
    virtual double toFloat() const = 0;
    virtual char toChar() const = 0;
    virtual string toString() const = 0;
};
