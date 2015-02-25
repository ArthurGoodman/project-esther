#include "selfcheckerfeature.h"

#include "runtime.h"
#include "object.h"

SelfCheckerFeature::SelfCheckerFeature(Class *selfClass)
    : selfClass(selfClass) {
}

void SelfCheckerFeature::check(Object *self, Tuple *) {
    if(!self->is(selfClass))
        Runtime::runtimeError("invalid self class");
}
