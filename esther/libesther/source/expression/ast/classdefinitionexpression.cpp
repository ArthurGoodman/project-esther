#include "classdefinitionexpression.h"

#include "context.h"
#include "runtime.h"
#include "class.h"

ClassDefinitionExpression::ClassDefinitionExpression(const std::string &name, Expression *superclass)
    : name(name), superclass(superclass) {
}

ClassDefinitionExpression::~ClassDefinitionExpression() {
    delete superclass;
}

Object *ClassDefinitionExpression::exec(Context *context) {
    Object *evaledSuperclass = superclass->eval(context);

    if (!dynamic_cast<Class *>(evaledSuperclass)) {
        setPosition(superclass->getPosition());
        Runtime::runtimeError("class expected");
    }

    return context->getRuntime()->createClass(name, (Class *)evaledSuperclass);
}
