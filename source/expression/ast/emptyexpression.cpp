#include "emptyexpression.h"

#include "runtime.h"

Object *EmptyExpression::eval(Context *) {
    return Runtime::getNull();
}
