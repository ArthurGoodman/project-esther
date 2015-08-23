#include "multisignature.h"

#include "overloadedmethod.h"

MultiSignature::MultiSignature(OverloadedMethod *method)
    : method(method) {
}

bool MultiSignature::accepts(Tuple *args) {
    list<Method *> methods = method->getMethods();

    foreach (i, methods)
        if ((*i)->getSignature()->accepts(args))
            return true;

    return false;
}

bool MultiSignature::equals(Signature *other) {
    list<Method *> methods = method->getMethods();

    foreach (i, methods)
        if ((*i)->getSignature()->equals(other))
            return true;

    return false;
}
