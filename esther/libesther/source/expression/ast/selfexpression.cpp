#include "selfexpression.h"

#include "esther.h"
#include "context.h"

Ptr<Object> SelfExpression::exec(Esther *esther) {
    return esther->context()->getSelf();
}
