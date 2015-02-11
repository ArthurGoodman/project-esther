#pragma once
#include "common.h"

namespace esther {

class Object;
class Context;

class FunctionBody {
public:
    virtual ~FunctionBody();

    virtual Object *eval(Context *context) = 0;
};
}
