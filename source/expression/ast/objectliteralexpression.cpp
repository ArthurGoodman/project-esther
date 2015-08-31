#include "objectliteralexpression.h"

#include "context.h"

ObjectLiteralExpression::ObjectLiteralExpression(Expression *body)
    : body(body) {
}

Object *ObjectLiteralExpression::exec(Context *context) {
    Object *object = new Object;
    body->eval(context->objectChildContext(object));
    return object;
}
