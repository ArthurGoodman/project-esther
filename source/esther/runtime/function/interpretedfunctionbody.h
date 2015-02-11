#pragma once
#include "common.h"

#include "functionbody.h"

namespace esther {

class Expression;

class InterpretedFunctionBody : public FunctionBody {
    Expression *e;

public:
    InterpretedFunctionBody(Expression *e);

    Object *eval(Context *context);
};
}
