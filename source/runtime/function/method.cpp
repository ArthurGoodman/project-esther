#include "method.h"

#include "selfcheckerfeature.h"
#include "staticselfcheckerfeature.h"

Method::Method(string className, string name, Context *context, Signature *signature, Block *body, Object *self, bool staticFlag)
    : Function(className, name, context, signature, body), staticFlag(staticFlag), self(self) {
    if (staticFlag)
        addFeature(new StaticSelfCheckerFeature(self, this));
    else
        addFeature(new SelfCheckerFeature((Class *)self, this));
}

Method::Method(string name, Context *context, Signature *signature, Block *body, Object *self, bool staticFlag)
    : Function("Method", name, context, signature, body), staticFlag(staticFlag), self(self) {
    if (staticFlag)
        addFeature(new StaticSelfCheckerFeature(self, this));
    else
        addFeature(new SelfCheckerFeature((Class *)self, this));
}

bool Method::isStatic() {
    return staticFlag;
}

Object *Method::getSelf() {
    return self;
}

bool Method::suitableFor(Object *self) {
    return staticFlag ? this->self == self : self->is((Class *)this->self);
}

string Method::toString() {
    return name.empty() ? "<anonymous method>" : "<method " + name + ">";
}

Object *Method::clone() {
    return new Method(name, name, context, signature, body, self, staticFlag);
}
