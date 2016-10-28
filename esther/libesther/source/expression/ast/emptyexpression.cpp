#include "emptyexpression.h"

#include "context.h"
#include "runtime.h"

Object *EmptyExpression::exec(Context *context) {
    return context->getRuntime()->getNull();
}
