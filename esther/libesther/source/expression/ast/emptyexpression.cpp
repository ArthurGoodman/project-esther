#include "emptyexpression.h"

#include "context.h"
#include "esther.h"

Pointer<Object> EmptyExpression::exec(Esther *esther) {
    return esther->getNull();
}
