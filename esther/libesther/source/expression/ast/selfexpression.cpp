#include "selfexpression.h"

#include "esther.h"
#include "context.h"

Object *SelfExpression::exec(Esther *esther) {
    return esther->context()->getSelf();
}
