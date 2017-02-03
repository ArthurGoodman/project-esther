#pragma once

#include "common/config.h"

#if HEAP_VARIANT

#include "variant/variant.h"

namespace es {

class VariantPrivate {
    friend class Variant;

public:
    virtual ~VariantPrivate();

private:
    virtual VariantPrivate *clone() const = 0;

    virtual Variant::Type type() const = 0;

    virtual int toInteger() const = 0;
    virtual double toReal() const = 0;
    virtual char toChar() const = 0;
    virtual std::string toString() const = 0;
};
}

#endif
