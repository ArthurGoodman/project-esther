#include "classdefinitionexpression.h"

#include "context.h"
#include "esther.h"
#include "class.h"

ClassDefinitionExpression::ClassDefinitionExpression(const std::string &name, Expression *superclass, Expression *body)
    : name(name)
    , superclass(superclass)
    , body(body) {
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

    Class *_class = esther->createClass(name, (Class *)evaledSuperclass);

    return _class;
}
