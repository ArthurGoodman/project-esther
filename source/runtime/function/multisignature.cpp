#include "multisignature.h"

#include "overloadedmethod.h"
#include "runtime.h"

MultiSignature::MultiSignature(OverloadedMethod *method)
    : method(method) {
}

bool MultiSignature::accepts(Tuple *args) {
    list<Method *> methods = method->getMethods();

    for (Method *m : methods)
        if (m->getSignature()->accepts(args))
            return true;

    return false;
}

void MultiSignature::apply(Tuple *args) {
    if (!accepts(args))
        Runtime::runtimeError("all overloads of " + method->toString() + " don't accept arguments");
}

Tuple *MultiSignature::convert(Tuple *args) {
    list<Method *> methods = method->getMethods();

    Method *firstAccept = 0;

    for (Method *m : methods) {
        if (m->getSignature()->accepts(args) && !firstAccept)
            firstAccept = m;

        if (m->getSignature()->check(args))
            return m->getSignature()->convert(args);
    }

    return firstAccept->getSignature()->convert(args);
}

bool MultiSignature::equals(Signature *other) {
    list<Method *> methods = method->getMethods();

    for (Method *m : methods)
        if (m->getSignature()->equals(other))
            return true;

    return false;
}

bool MultiSignature::weakEquals(Signature *other) {
    list<Method *> methods = method->getMethods();

    for (Method *m : methods)
        if (m->getSignature()->weakEquals(other))
            return true;

    return false;
}

Object *MultiSignature::clone() {
    return new MultiSignature(method);
}
