#include "objectliteralexpression.h"

#include "context.h"

ObjectLiteralExpression::ObjectLiteralExpression(Expression *body)
    : body(body) {
}

ObjectLiteralExpression::~ObjectLiteralExpression() {
    delete body;
}

Object *ObjectLiteralExpression::eval(Context *context) {
    Object *object = new Object;
    body->eval(context->objectChildContext(object));
    return object;
}
