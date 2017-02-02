#include "classdefinitionexpression.h"

#include "runtime/context.h"
#include "runtime/esther.h"
#include "runtime/class.h"

ClassDefinitionExpression::ClassDefinitionExpression(const std::string &name, Expression *superclass)
    : name(name)
    , superclass(superclass) {
}

ClassDefinitionExpression::~ClassDefinitionExpression() {
    delete superclass;
}

Ptr<Object> ClassDefinitionExpression::exec(Esther *esther) {
    Ptr<Object> evaledSuperclass = superclass->eval(esther);

    if (!dynamic_cast<Class *>(*evaledSuperclass)) {
        setPosition(superclass->getPosition());
        Esther::runtimeError("class expected");
    }

    return new Class(esther, name, static_cast<Class *>(*evaledSuperclass));
}
