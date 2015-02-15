#include "hereexpression.h"

#include "context.h"

Object *HereExpression::eval(Context *context) {
    return context;
}
