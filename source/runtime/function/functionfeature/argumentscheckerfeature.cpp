#include "argumentscheckerfeature.h"

#include "runtime.h"
#include "signature.h"

ArgumentsCheckerFeature::ArgumentsCheckerFeature(Signature *signature)
    : signature(signature) {
}

void ArgumentsCheckerFeature::check(IObject *, Tuple *args) {
    signature->apply(args);
}
