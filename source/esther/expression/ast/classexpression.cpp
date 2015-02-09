#include "classexpression.h"

#include "runtime.h"
#include "context.h"
#include "class.h"

namespace esther {

ClassExpression::ClassExpression(Expression *name, Expression *superclass, Expression *body)
    : name(name), superclass(superclass), body(body) {
}

Object *ClassExpression::eval(Context *context) {
    string name;
    Class *_class = 0, *superclass = 0;

    if (this->superclass) {
        superclass = (Class *)this->superclass->eval(context);

        if (!superclass->is(Runtime::getRootClass("Class")))
            Runtime::runtimeError("class expected");
    }

    if (this->name) {
        name = this->name->eval(context)->toString();

        if (context->hasId(name))
            _class = (Class *)context->getId(name);
    }

    if (!_class || !_class->is(Runtime::getRootClass("Class")))
        _class = new Class(name, superclass);

    body->eval(context->childContext(_class, _class));

    context->setLocal(name, _class);

    return _class;
}
}
