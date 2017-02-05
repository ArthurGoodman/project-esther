#include "expression/ast/classdefinitionexpression.h"

#include "esther.h"
#include "runtime/context.h"
#include "runtime/class.h"

namespace es {

ClassDefinitionExpression::ClassDefinitionExpression(const std::string &name, Expression *superclass)
    : name(name)
    , superclass(superclass) {
}

ClassDefinitionExpression::~ClassDefinitionExpression() {
    delete superclass;
}

Object *ClassDefinitionExpression::exec(Esther *esther) {
    Object *evaledSuperclass = superclass->eval(esther);

    if (!dynamic_cast<Class *>(evaledSuperclass)) {
        setPosition(superclass->getPosition());
        Esther::runtimeError("class expected");
    }

    return new Class(esther, name, static_cast<Class *>(evaledSuperclass));
}
}
