#include "continueexpression.h"

#include "esther.h"
#include "continueexception.h"

Object *ContinueExpression::eval(Context *) {
    throw new ContinueException;
}
