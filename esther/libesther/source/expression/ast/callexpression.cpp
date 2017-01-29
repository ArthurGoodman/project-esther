#include "callexpression.h"

#include "context.h"
#include "esther.h"
#include "function.h"

CallExpression::CallExpression(const std::string &name, const std::list<Expression *> &args)
    : name(name)
    , args(args) {
}

CallExpression::~CallExpression() {
    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Esther *esther) {
    Object *f = esther->context()->get(name);

    if (f == nullptr)
        Esther::runtimeError("undefined identifier '" + name + "'");

    if (dynamic_cast<Function *>(f)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return ((Function *)f)->invoke(esther, esther->context()->getSelf(), evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << esther->context()->getSelf();

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return f->call(esther, "()", evaledArgs);
    }
}
