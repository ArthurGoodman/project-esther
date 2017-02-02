#include "continueexception.h"

void ContinueException::raise() {
    throw this;
}
