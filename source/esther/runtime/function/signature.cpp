#include "signature.h"

namespace esther {

Signature::Signature(Class *returnType, list<Class *> argsTypes)
    : returnType(returnType), argsTypes(argsTypes) {
}
}
