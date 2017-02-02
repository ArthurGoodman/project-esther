#include "emptyexpression.h"

#include "runtime/context.h"
#include "runtime/esther.h"

Ptr<Object> EmptyExpression::exec(Esther *esther) {
    return esther->getNull();
}
