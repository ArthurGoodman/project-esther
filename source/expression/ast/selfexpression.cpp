#include "selfexpression.h"

#include "context.h"

Object *SelfExpression::eval(Context *context) {
    return context->getCurrentSelf();
}
