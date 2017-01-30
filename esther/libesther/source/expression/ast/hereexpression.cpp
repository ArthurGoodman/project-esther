#include "hereexpression.h"

#include "esther.h"
#include "context.h"

Pointer<Object> HereExpression::exec(Esther *esther) {
    return esther->context()->getHere();
}
