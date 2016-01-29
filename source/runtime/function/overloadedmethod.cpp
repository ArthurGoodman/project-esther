#include "overloadedmethod.h"

#include "common.h"
#include "runtime.h"
#include "block.h"
#include "multisignature.h"
#include "overloadedmethodblock.h"

OverloadedMethod::OverloadedMethod(const std::string &name, IObject *self, bool staticFlag)
    : NativeMethod("OverloadedMethod", name, 0, new MultiSignature(this), new OverloadedMethodBlock(this), self, staticFlag) {
}

void OverloadedMethod::addMethod(Method *method) {
    methods << method;
}

std::list<Method *> OverloadedMethod::getMethods() {
    return methods;
}

void OverloadedMethod::replaceMethod(Method *method) {
    for (Method *&m : methods)
        if (m->getSignature()->weakEquals(method->getSignature())) {
            m = method;
            break;
        }
}

IObject *OverloadedMethod::clone() {
    OverloadedMethod *clone = new OverloadedMethod(name, getSelf(), isStatic());
    clone->methods = methods;
    return clone;
}
