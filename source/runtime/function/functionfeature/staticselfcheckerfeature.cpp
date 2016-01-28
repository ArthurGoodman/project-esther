#include "staticselfcheckerfeature.h"

#include "runtime.h"
#include "object.h"
#include "method.h"

StaticSelfCheckerFeature::StaticSelfCheckerFeature(IObject *self, Method *method)
    : self(self), method(method) {
}

void StaticSelfCheckerFeature::check(IObject *self, Tuple *) {
    if (self != this->self)
        Runtime::runtimeError(self->callToString() + " is not a valid self object for " + method->callToString() + " (" + this->self->callToString() + " expected)");
}
