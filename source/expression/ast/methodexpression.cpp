#include "methodexpression.h"

#include "runtime.h"
#include "class.h"
#include "parameter.h"
#include "method.h"
#include "signature.h"
#include "context.h"
#include "interpretedblock.h"

MethodExpression::MethodExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic)
    : type(type), name(name), params(params), body(body), variadic(variadic), dynamic(dynamic) {
}

Object *MethodExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class"))
        Runtime::runtimeError("class expected");

    string name = this->name ? (dynamic ? this->name->eval(context)->toString() : this->name->eval(context)->immediateToString()) : "";

    list<Parameter *> evaledParams;

    for (Expression *e : params)
        evaledParams << (Parameter *)e->eval(context);

    bool isStatic = context->getModifier(Context::StaticModifier);
    Object *self = (isStatic || dynamic_cast<Class *>(context->getCurrentSelf())) ? context->getCurrentSelf() : (Object *)context->getCurrentClass();

    Method *f = new Method(name, context, new Signature(type, evaledParams, variadic), new InterpretedBlock(body), self, isStatic);

    if (!name.empty()) {
        if (dynamic_cast<Class *>(context->getCurrentSelf()))
            ((Class *)context->getCurrentSelf())->setMethod(f);
        else
            context->setLocal(name, f);
    }

    return f;
}
