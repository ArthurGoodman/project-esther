#include "selfexpression.h"

#include "runtime/esther.h"
#include "runtime/context.h"

Ptr<Object> SelfExpression::exec(Esther *esther) {
    return esther->context()->getSelf();
}
