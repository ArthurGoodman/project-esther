#include "hereexpression.h"

#include "esther.h"
#include "context.h"

Object *HereExpression::exec(Esther *esther) {
    return esther->getContext()->getHere();
}
