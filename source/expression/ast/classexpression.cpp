#include "classexpression.h"

#include "runtime.h"
#include "context.h"
#include "class.h"

ClassExpression::ClassExpression(Expression *name, Expression *superclass, Expression *body)
    : name(name), superclass(superclass), body(body) {
}

Object *ClassExpression::eval(Context *context) {
    context = context->childContext();

    string name;
    Class *_class = 0, *superclass = 0;

    if (this->superclass) {
        superclass = (Class *)this->superclass->eval(context);

        if (!superclass->is("Class"))
            Runtime::runtimeError("class expected");
    }

    if (this->name) {
        name = this->name->eval(context)->toString();

        if (context->hasId(name))
            _class = (Class *)context->getId(name);
    }

    if (!_class || !_class->is("Class"))
        _class = new Class(name, superclass);

    body->eval(context->objectChildContext(_class, _class));

    if (!name.empty())
        context->setLocal(name, _class);

    return _class;
}
