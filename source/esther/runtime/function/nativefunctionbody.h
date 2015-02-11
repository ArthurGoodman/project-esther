#pragma once
#include "common.h"

#include "functionbody.h"

namespace esther {

class Tuple;

class NativeFunctionBody : public FunctionBody {
    function<Object *(Object *, Tuple *)> f;

public:
    NativeFunctionBody(function<Object *(Object *, Tuple *)> f);

    Object *eval(Context *context);
};
}
