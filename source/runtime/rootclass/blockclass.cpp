#include "blockclass.h"

#include "interpretedblock.h"
#include "expression.h"
#include "block.h"
#include "tuple.h"
#include "signature.h"

BlockClass::BlockClass()
    : RootClass("Block") {
}

Object *BlockClass::newInstance() {
    return new InterpretedBlock(Expression::Empty());
}

void BlockClass::setupMethods() {
    auto evalMethod = [](Object * self, Tuple * args) -> Object * {
        return ((Block *)self)->eval((Context *)args->at(0));
    };

    setMethod("eval", new Signature("Object", {"Context"}), evalMethod);
}
