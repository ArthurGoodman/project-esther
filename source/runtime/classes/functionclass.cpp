#include "functionclass.h"

#include "runtime.h"
#include "function.h"
#include "interpretedblock.h"
#include "expression.h"
#include "tuple.h"

FunctionClass::FunctionClass()
    : RootClass("Function") {
}

Object *FunctionClass::newInstance() {
    return new Function("", Runtime::getRoot(), {}, new InterpretedBlock(Expression::Empty()));
}

void FunctionClass::setupMethods() {
    auto parenthesesMethod = [](Object * self, Tuple * args) -> Object * {
        list<Object *> argsList;

        for (int i = 1; i < args->size(); i++)
            argsList << args->at(i);

        Object *value = ((Function *)self)->invoke(args->at(0), new Tuple(argsList));
        return value;
    };

    setMethod("()", parenthesesMethod);
}
