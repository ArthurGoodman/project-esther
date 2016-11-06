#include "directcallexpression.h"

#include "common.h"

DirectCallExpression::DirectCallExpression(Expression *self, Expression *name, const std::list<Expression *> &args)
    : self(self), name(name), args(args) {
}

DirectCallExpression::~DirectCallExpression() {
    delete self;
    delete name;

    for (Expression *e : args)
        delete e;
}

Object *DirectCallExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);
    std::string name = this->name->eval(context)->toString();

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    return evaledSelf->call(name, evaledArgs);
}
