#include "functionclass.h"

#include "runtime.h"
#include "function.h"
#include "interpretedblock.h"
#include "expression.h"
#include "tuple.h"
#include "context.h"
#include "signature.h"
#include "method.h"

FunctionClass::FunctionClass()
    : RootClass("Function") {
}

Object *FunctionClass::newInstance() {
    return new Function("", Runtime::getRoot(), new Signature, {}, new InterpretedBlock(Expression::Empty()));
}

void FunctionClass::setupMethods() {
    auto parenthesesMethod = [](Object * self, Tuple * args) -> Object * {
        Object *value = ((Function *)self)->invoke(((Context *)args->at(0))->getCurrentSelf(), (Tuple *)args->at(1));
        return value;
    };

    setMethod("call", new Signature("Object", {"Context", "Tuple"}), parenthesesMethod);
    setAttribute("()", getMethod("call"));
}
