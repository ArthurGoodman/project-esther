#include "continueexception.h"

namespace esther {

void ContinueException::raise() {
    throw this;
}
}
