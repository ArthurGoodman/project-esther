#include "blockclass.h"

#include "interpretedblock.h"
#include "expression.h"
#include "block.h"
#include "tuple.h"
#include "signature.h"

BlockClass::BlockClass()
    : RootClass("Block") {
}

void BlockClass::setupMethods() {
    auto evalMethod = [](IObject *self, Tuple *args) -> IObject * {
        return ((Block *)self)->eval((Context *)args->at(0));
    };

    setMethod("eval", new Signature("Object", {"Context"}), evalMethod);
}

IObject *BlockClass::createNewInstance() {
    return new InterpretedBlock(Expression::Empty());
}
