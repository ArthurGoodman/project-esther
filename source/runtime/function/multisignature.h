#pragma once
#include "common.h"

#include "signature.h"

class OverloadedMethod;

class MultiSignature : public Signature {
    OverloadedMethod *method;

public:
    MultiSignature(OverloadedMethod *method);

    bool accepts(Tuple *args);
};
