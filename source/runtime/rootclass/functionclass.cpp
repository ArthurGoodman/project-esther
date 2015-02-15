#include "functionclass.h"

#include "runtime.h"
#include "function.h"
#include "interpretedblock.h"
#include "expression.h"
#include "tuple.h"
#include "context.h"

FunctionClass::FunctionClass()
    : RootClass("Function") {
}

Object *FunctionClass::newInstance() {
    return new Function("", Runtime::getRoot(), {}, new InterpretedBlock(Expression::Empty()));
}

void FunctionClass::setupMethods() {
    auto parenthesesMethod = [](Object * self, Tuple * args) -> Object * {
        Object *value = ((Function *)self)->invoke(((Context *)args->at(0))->getCurrentSelf(), (Tuple *)args->at(1));
        return value;
    };

    setMethod("()", parenthesesMethod);
}
