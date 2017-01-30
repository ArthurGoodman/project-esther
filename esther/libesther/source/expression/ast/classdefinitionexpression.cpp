#include "classdefinitionexpression.h"

#include "context.h"
#include "esther.h"
#include "class.h"

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

    return esther->createClass(name, (Class *)evaledSuperclass);
}
