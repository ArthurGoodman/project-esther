#include "selfexpression.h"

#include "context.h"

IObject *SelfExpression::exec(Context *context) {
    return context->getCurrentSelf();
}
