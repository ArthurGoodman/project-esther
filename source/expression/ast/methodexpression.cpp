#include "methodexpression.h"

#include "common.h"
#include "runtime.h"
#include "class.h"
#include "parameter.h"
#include "method.h"
#include "signature.h"
#include "context.h"
#include "interpretedblock.h"

MethodExpression::MethodExpression(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic)
    : type(type), name(name), params(params), body(body), variadic(variadic), dynamic(dynamic) {
}

IObject *MethodExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class")) {
        setPosition(this->type->getPosition());
        Runtime::runtimeError("class expected in method return type");
    }

    std::string name = this->name ? (dynamic ? this->name->eval(context)->callToString() : this->name->eval(context)->toString()) : "";

    std::list<Parameter *> evaledParams;

    for (Expression *e : params)
        evaledParams << (Parameter *)e->eval(context);

    bool isStatic = context->getModifier(Context::StaticModifier);
    IObject *self = (isStatic || dynamic_cast<Class *>(context->getCurrentSelf())) ? context->getCurrentSelf() : (IObject *)context->getCurrentClass();

    Method *f = new Method(name, context, new Signature(type, evaledParams, variadic), new InterpretedBlock(body), self, isStatic);

    if (!name.empty()) {
        if (dynamic_cast<Class *>(context->getCurrentSelf()))
            ((Class *)context->getCurrentSelf())->setMethod(f);
        else
            context->setLocal(name, f);
    }

    return f;
}
