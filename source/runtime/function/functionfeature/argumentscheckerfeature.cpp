#include "argumentscheckerfeature.h"

#include "runtime.h"
#include "signature.h"

ArgumentsCheckerFeature::ArgumentsCheckerFeature(Signature *signature)
    : signature(signature) {
}

void ArgumentsCheckerFeature::check(Object *, Tuple *args) {
    if (!signature->accepts(args))
        Runtime::runtimeError("invalid arguments");
}
