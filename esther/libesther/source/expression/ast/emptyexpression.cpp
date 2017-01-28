#include "emptyexpression.h"

#include "context.h"
#include "esther.h"

Object *EmptyExpression::exec(Esther *esther) {
    return esther->getNull();
}
