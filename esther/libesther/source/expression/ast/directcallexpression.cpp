#include "directcallexpression.h"

#include "common.h"

DirectCallExpression::DirectCallExpression(Expression *self, const std::string &name, const std::list<Expression *> &args)
    : self(self), name(name), args(args) {
}

DirectCallExpression::~DirectCallExpression() {
    delete self;

    for (Expression *e : args)
        delete e;
}

Object *DirectCallExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    return evaledSelf->call(name, evaledArgs);
}
