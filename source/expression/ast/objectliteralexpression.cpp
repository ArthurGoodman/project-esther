#include "objectliteralexpression.h"

#include "iobject.h"
#include "context.h"

ObjectLiteralExpression::ObjectLiteralExpression(Expression *body)
    : body(body) {
}

IObject *ObjectLiteralExpression::exec(Context *context) {
    IObject *object = new Object;
    body->eval(context->objectChildContext(object));
    return object;
}
