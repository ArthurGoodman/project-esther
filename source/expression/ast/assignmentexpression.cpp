#include "assignmentexpression.h"

#include "common.h"
#include "iobject.h"
#include "identifierdefinitionexpression.h"
#include "identifierexpression.h"
#include "tupleexpression.h"
#include "objectcontext.h"
#include "runtime.h"
#include "tuple.h"

AssignmentExpression::AssignmentExpression(Expression *expression, Expression *value)
    : expression(expression), value(value) {
}

IObject *AssignmentExpression::exec(Context *context) {
    if (dynamic_cast<IdentifierDefinitionExpression *>(expression)) {
        ((IdentifierDefinitionExpression *)expression)->setValue(value);
        return expression->eval(context);
    }

    std::list<Expression *> expressions;

    if (dynamic_cast<TupleExpression *>(expression))
        expressions = ((TupleExpression *)expression)->getNodes();
    else
        expressions << expression;

    std::list<IObject *> values;

    if (dynamic_cast<TupleExpression *>(value))
        for (Expression *e : ((TupleExpression *)value)->getNodes())
            values << e->eval(context);
    else {
        IObject *value = this->value->eval(context);

        if (dynamic_cast<Tuple *>(value))
            for (IObject *obj : *(Tuple *)value)
                values << obj;
        else
            values << value;
    }

    std::list<IObject *>::iterator i = values.begin();

    IObject *result = Runtime::getNull();

    for (Expression *e : expressions) {
        IObject *value = i != values.end() ? *i : Runtime::getNull();

        if (dynamic_cast<IdentifierExpression *>(e)) {
            IdentifierExpression *ie = (IdentifierExpression *)e;

            std::string name = ie->isDynamic() ? ie->getName()->eval(context)->callToString() : ie->getName()->eval(context)->toString();

            if (dynamic_cast<ObjectContext *>(context) || !context->setId(name, value))
                context->setLocal(name, value);

            result = value;
        } else
            result = e->eval(context)->call("=", value);

        if (i != values.end())
            ++i;
    }

    return result;
}
