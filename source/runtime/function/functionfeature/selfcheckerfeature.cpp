#include "selfcheckerfeature.h"

#include "runtime.h"
#include "object.h"
#include "method.h"
#include "class.h"

SelfCheckerFeature::SelfCheckerFeature(Class *selfClass, Method *method)
    : selfClass(selfClass), method(method) {
}

void SelfCheckerFeature::check(IObject *self, Tuple *) {
    if (!self->is(selfClass))
        Runtime::runtimeError(self->getClass()->callToString() + " is not a valid self class for " + method->callToString() + " (" + selfClass->callToString() + " expected)");
}
