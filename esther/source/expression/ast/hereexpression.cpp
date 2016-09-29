#include "hereexpression.h"

#include "context.h"

Object *HereExpression::exec(Context *context) {
    return context->getHere();
}
