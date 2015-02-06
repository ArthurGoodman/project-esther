#include "emptyexpression.h"

#include "runtime.h"

namespace esther {

Object *EmptyExpression::eval(Context *) {
    return Runtime::getNull();
}
}
