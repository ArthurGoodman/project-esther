#include "staticexpression.h"

#include "context.h"

StaticExpression::StaticExpression(Expression *body)
    : body(body) {
}

IObject *StaticExpression::exec(Context *context) {
    int modifier = context->getModifier(Context::StaticModifier);

    context->setModifier(Context::StaticModifier, true);
    IObject *value = body->eval(context);
    context->setModifier(Context::StaticModifier, modifier);

    return value;
}
