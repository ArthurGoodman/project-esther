#include "functionexpression.h"

#include "runtime.h"
#include "class.h"
#include "parameter.h"
#include "function.h"
#include "signature.h"
#include "context.h"
#include "interpretedblock.h"

FunctionExpression::FunctionExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body)
    : type(type), name(name), params(params), body(body) {
}

Object *FunctionExpression::eval(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class"))
        Runtime::runtimeError("class expected");

    string name = this->name->eval(context)->toString();

    list<Parameter *> evaledParams;

    foreach (i, params)
        evaledParams << (Parameter *)(*i)->eval(context);

    Function *f = new Function(name, context, new Signature(type, evaledParams), new InterpretedBlock(body));

    if (!name.empty())
        context->setLocal(name, f);

    return f;
}
