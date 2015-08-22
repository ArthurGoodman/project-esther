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

void FunctionClass::setupMethods() {
    auto callMethod = [](Object *self, Tuple *args) -> Object *{
        Object *value = ((Function *)self)->invoke(((Context *)args->at(0))->getCurrentSelf(), (Tuple *)args->at(1));
        return value;
    };

    setMethod("call", new Signature("Object", {"Context", "Tuple"}), callMethod);
    setAttribute("()", getMethod("call"));

    auto bodyMethod = [](Object *self, Tuple *) -> Object *{
        return ((Function *)self)->getBody();
    };

    setMethod("body", new Signature("Block", {}), bodyMethod);
}

Object *FunctionClass::createNewInstance() {
    return new Function("", Runtime::getRoot(), new Signature, new InterpretedBlock(Expression::Empty()));
}
