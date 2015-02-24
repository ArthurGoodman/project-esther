#include "staticexpression.h"

#include "context.h"

StaticExpression::StaticExpression(Expression *body)
    : body(body) {
}

Object *StaticExpression::eval(Context *context) {
    int modifier = context->getModifier(Context::StaticModifier);

    context->setModifier(Context::StaticModifier, true);
    Object *value = body->eval(context);
    context->setModifier(Context::StaticModifier, modifier);

    return value;
}
