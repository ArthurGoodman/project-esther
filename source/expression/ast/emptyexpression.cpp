#include "emptyexpression.h"

#include "runtime.h"

IObject *EmptyExpression::exec(Context *) {
    return Runtime::getNull();
}
