#include "emptyexpression.h"

#include "runtime.h"

Object *EmptyExpression::exec(Context *) {
    return Runtime::getNull();
}
