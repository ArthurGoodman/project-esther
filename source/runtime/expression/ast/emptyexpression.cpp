#include "emptyexpression.h"

#include "esther.h"

namespace esther {

Object *EmptyExpression::eval(Context *) {
    return Esther::getNull();
}
}
