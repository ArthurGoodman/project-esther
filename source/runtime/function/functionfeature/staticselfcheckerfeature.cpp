#include "staticselfcheckerfeature.h"

#include "runtime.h"
#include "object.h"

StaticSelfCheckerFeature::StaticSelfCheckerFeature(Object *self)
    : self(self) {
}

void StaticSelfCheckerFeature::check(Object *self, Tuple *) {
    if(self != this->self)
        Runtime::runtimeError("invalid self");
}
