#include "functionexpression.h"

#include "common.h"
#include "runtime.h"
#include "class.h"
#include "parameter.h"
#include "function.h"
#include "signature.h"
#include "context.h"
#include "interpretedblock.h"

FunctionExpression::FunctionExpression(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic)
    : type(type), name(name), params(params), body(body), variadic(variadic), dynamic(dynamic) {
}

IObject *FunctionExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class")) {
        setPosition(this->type->getPosition());
        Runtime::runtimeError("class expected in function return type");
    }

    std::string name = this->name ? (dynamic ? this->name->eval(context)->callToString() : this->name->eval(context)->toString()) : "";

    std::list<Parameter *> evaledParams;

    for (Expression *e : params)
        evaledParams << (Parameter *)e->eval(context);

    Function *f = new Function(name, context, new Signature(type, evaledParams, variadic), new InterpretedBlock(body));

    if (!name.empty())
        context->setLocal(name, f);

    return f;
}
