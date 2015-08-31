#include "continueexpression.h"

#include "esther.h"
#include "continueexception.h"

Object *ContinueExpression::exec(Context *) {
    throw new ContinueException;
}
