#include "exception/continueexception.h"

namespace es {

void ContinueException::raise() {
    throw this;
}
}
