#include "continueexpression.h"

#include "esther.h"
#include "continueexception.h"

IObject *ContinueExpression::exec(Context *) {
    throw new ContinueException;
}
