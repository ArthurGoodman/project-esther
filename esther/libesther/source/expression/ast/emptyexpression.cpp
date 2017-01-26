#include "emptyexpression.h"

#include "context.h"
#include "esther.h"

Object *EmptyExpression::exec(Context *context) {
    return context->getRuntime()->getNull();
}
