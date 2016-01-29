#include "method.h"

#include "selfcheckerfeature.h"
#include "staticselfcheckerfeature.h"

Method::Method(const std::string &className, const std::string &name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag)
    : Function(className, name, context, signature, body), staticFlag(staticFlag), self(self) {
    if (staticFlag)
        addFeature(new StaticSelfCheckerFeature(self, this));
    else
        addFeature(new SelfCheckerFeature((Class *)self, this));
}

Method::Method(const std::string &name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag)
    : Function("Method", name, context, signature, body), staticFlag(staticFlag), self(self) {
    if (staticFlag)
        addFeature(new StaticSelfCheckerFeature(self, this));
    else
        addFeature(new SelfCheckerFeature((Class *)self, this));
}

bool Method::isStatic() {
    return staticFlag;
}

IObject *Method::getSelf() {
    return self;
}

bool Method::suitableFor(IObject *self) {
    return staticFlag ? this->self == self : self->is((Class *)this->self);
}

std::string Method::toString() {
    return name.empty() ? "<anonymous method>" : "<method " + name + ">";
}

IObject *Method::clone() {
    return new Method(name, name, context, signature, body, self, staticFlag);
}
