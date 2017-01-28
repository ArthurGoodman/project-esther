#include "directcallexpression.h"

#include "common.h"

DirectCallExpression::DirectCallExpression(Expression *self, const std::string &name, const std::list<Expression *> &args)
    : self(self)
    , name(name)
    , args(args) {
}

DirectCallExpression::~DirectCallExpression() {
    delete self;

    for (Expression *e : args)
        delete e;
}

Object *DirectCallExpression::exec(Esther *esther) {
    Object *evaledSelf = self->eval(esther);

    std::vector<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(esther);

    return evaledSelf->call(esther, name, evaledArgs);
}
