#include "overloadedmethod.h"

#include "runtime.h"
#include "block.h"
#include "multisignature.h"
#include "overloadedmethodblock.h"

OverloadedMethod::OverloadedMethod(string name, Object *self, bool staticFlag)
    : NativeMethod("OverloadedMethod", name, 0, new MultiSignature(this), new OverloadedMethodBlock(this), self, staticFlag) {
}

void OverloadedMethod::addMethod(Method *method) {
    methods << method;
}

list<Method *> OverloadedMethod::getMethods() {
    return methods;
}
