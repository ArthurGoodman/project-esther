#include "signature.h"

Signature::Signature(Class *returnType, list<Class *> argsTypes)
    : returnType(returnType), argsTypes(argsTypes) {
}
