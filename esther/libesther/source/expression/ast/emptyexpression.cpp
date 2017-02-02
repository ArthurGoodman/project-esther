#include "emptyexpression.h"

#include "context.h"
#include "esther.h"

Ptr<Object> EmptyExpression::exec(Esther *esther) {
    return esther->getNull();
}
