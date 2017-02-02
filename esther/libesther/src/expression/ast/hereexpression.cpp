#include "hereexpression.h"

#include "runtime/esther.h"
#include "runtime/context.h"

Ptr<Object> HereExpression::exec(Esther *esther) {
    return esther->context()->getHere();
}
