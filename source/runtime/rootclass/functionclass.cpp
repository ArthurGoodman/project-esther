#include "functionclass.h"

#include "runtime.h"
#include "function.h"
#include "interpretedblock.h"
#include "expression.h"
#include "tuple.h"
#include "context.h"
#include "signature.h"
#include "method.h"
#include "string.h"

FunctionClass::FunctionClass()
    : RootClass("Function") {
}

void FunctionClass::setupMethods() {
    auto callMethod = [](IObject *self, Tuple *args) -> IObject * {
        IObject *value = ((Function *)self)->invoke(args->at(0), (Tuple *)args->at(1));
        return value;
    };

    setMethod("call", new Signature("Object", {"Object", "Tuple"}), callMethod);
    setAttribute("()", getMethod("call"));

    auto bodyMethod = [](IObject *self, Tuple *) -> IObject * {
        return ((Function *)self)->getBody();
    };

    setMethod("body", new Signature("Block", {}), bodyMethod);
}

IObject *FunctionClass::createNewInstance() {
    return new Function("", Runtime::getRoot(), new Signature, new InterpretedBlock(Expression::Empty()));
}
