#include "hereexpression.h"

#include "context.h"

IObject *HereExpression::exec(Context *context) {
    return context;
}
