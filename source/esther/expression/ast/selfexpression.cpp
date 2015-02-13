#include "selfexpression.h"

#include "context.h"

namespace esther {

Object *SelfExpression::eval(Context *context) {
    return context->getCurrentSelf();
}
}
