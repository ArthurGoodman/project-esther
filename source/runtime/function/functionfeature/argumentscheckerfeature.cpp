#include "argumentscheckerfeature.h"

#include "runtime.h"
#include "signature.h"

ArgumentsCheckerFeature::ArgumentsCheckerFeature(Signature *signature)
    : signature(signature) {
}

void ArgumentsCheckerFeature::check(Object *, Tuple *args) {
    signature->apply(args);
}
