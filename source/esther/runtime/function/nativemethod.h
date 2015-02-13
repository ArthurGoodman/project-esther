#pragma once
#include "common.h"

#include "functionbody.h"

namespace esther {

class Tuple;

class NativeMethod : public FunctionBody {
    function<Object *(Object *, Tuple *)> f;

public:
    NativeMethod(function<Object *(Object *, Tuple *)> f);

    Object *eval(Context *context);
};
}
