#include "interpretedfunctionbody.h"

#include "expression.h"

namespace esther {

InterpretedFunctionBody::InterpretedFunctionBody(Expression *e)
    : e(e) {
}

Object *InterpretedFunctionBody::eval(Context *context) {
    return e->eval(context);
}
}
