#include "method.h"

#include "selfcheckerfeature.h"
#include "staticselfcheckerfeature.h"

Method::Method(string name, Context *context, Signature *signature, Block *body, Object *self, bool staticFlag)
    : Function("Method", name, context, signature, body), staticFlag(staticFlag) {
    if (staticFlag)
        addFeature(new StaticSelfCheckerFeature(self));
    else
        addFeature(new SelfCheckerFeature((Class *)self));
}

string Method::toString() {
    return name.empty() ? "<anonymous method>" : "<method " + name + ">";
}

bool Method::isStatic() {
    return staticFlag;
}
