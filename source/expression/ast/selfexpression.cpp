#include "selfexpression.h"

#include "context.h"

Object *SelfExpression::exec(Context *context) {
    return context->getCurrentSelf();
}
