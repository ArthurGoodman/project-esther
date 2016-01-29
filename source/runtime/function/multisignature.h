#pragma once

#include "signature.h"

class OverloadedMethod;

class MultiSignature : public Signature {
    OverloadedMethod *method;

public:
    MultiSignature(OverloadedMethod *method);

    bool accepts(Tuple *args);
    void apply(Tuple *args);

    Tuple *convert(Tuple *args);

    bool equals(Signature *other);
    bool weakEquals(Signature *other);

    IObject *clone();
};
